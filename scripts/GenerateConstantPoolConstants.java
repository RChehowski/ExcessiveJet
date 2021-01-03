import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;
import java.util.StringJoiner;

public class GenerateConstantPoolConstants
{
    private static class Const
    {
        private static final String GenNamespace = "Parse";
        private static final String GenReaderNamespace = "Util";

        private static final String GenReaderClass = "MemoryReader";
        private static final String GenBaseClass = "ConstantInfo";

        private static final String GenDeserializeMethod = "DeserializeFrom";
    }

    private static class Pair<TFirst, TSecond>
    {
        public final TFirst First;
        public final TSecond Second;

        private Pair(TFirst first, TSecond second)
        {
            First = first;
            Second = second;
        }

        public static<TFirst, TSecond> Pair<TFirst, TSecond> of(TFirst First, TSecond Second)
        {
            return new Pair<>(First, Second);
        }
    }

    private static class ClassDesc implements Iterable<Pair<String, String>>
    {
        private final String Name;
        private final List<Pair<String, String>> Fields;

        public ClassDesc(final String InName, final List<Pair<String, String>> InFields)
        {
            Name = InName;
            Fields = InFields;
        }

        @Override
        public Iterator<Pair<String, String>> iterator()
        {
            return Fields.iterator();
        }

        public final String GetFullName()
        {
            return "Constant" + Name + "Info";
        }
    }

    public static void DeleteDir(final Path DirPath) throws IOException
    {
        final File DirFile = Objects.requireNonNull(DirPath.toFile());
        if (Files.isDirectory(DirPath))
        {
            final File[] FilesInDirectory = DirFile.listFiles();
            if (FilesInDirectory != null)
            {
                for (File FileInDirectory : FilesInDirectory)
                {
                    if (FileInDirectory.isDirectory())
                    {
                        // Recurse
                        DeleteDir(FileInDirectory.toPath());
                    }
                    else
                    {
                        assert FileInDirectory.delete();
                    }
                }
            }
        }
        else
        {
            Files.deleteIfExists(DirPath);
        }
    }

    private static String GetHeaderContent(final ClassDesc Desc)
    {
        final StringJoiner s = new StringJoiner(System.lineSeparator());

        s.add("#pragma once");
        s.add("");
        s.add("#include \"ConstantPool/" + Const.GenBaseClass + ".h\"");
        s.add("");

        // Declare reader class
        s.add("namespace " + Const.GenReaderNamespace);
        s.add("{");
        s.add("    class C" + Const.GenReaderClass + ";");
        s.add("}");
        s.add("");

        s.add("namespace " + Const.GenNamespace);
        s.add("{");
        s.add("    class C" + Desc.GetFullName() + " : public C" + Const.GenBaseClass);
        s.add("    {");
        s.add("    public:");

        // Inherited constructor
        s.add("        using C" + Const.GenBaseClass + "::C" + Const.GenBaseClass + ";");
        s.add("");

        // ToString()
        s.add("        std::string ToString() const override;");
        s.add("");

        // Getters
        for (final Pair<String, String> Pair : Desc)
        {
        s.add("        [[nodiscard]]");
        s.add("        FORCEINLINE " + Pair.First + " Get" + Pair.Second + "() const");
        s.add("        {");
        s.add("             return " + Pair.Second + ";");
        s.add("        }");
        s.add("");
        }

        // Deserialize method
        s.add("        void " + Const.GenDeserializeMethod + "(" + Const.GenReaderNamespace + "::C" + Const.GenReaderClass + "& Reader) override;");
        s.add("");

        // Operator>>
        s.add("        friend void operator>>(" + Const.GenReaderNamespace + "::C" + Const.GenReaderClass + "& Reader, C" + Desc.GetFullName() + "& Instance);");
        s.add("");

        s.add("    private:");

        // Fields
        for (final Pair<String, String> Pair : Desc)
        {
        s.add("        " + Pair.First + " " + Pair.Second + " = (" + Pair.First + ")0;");
        }
        s.add("    };");
        s.add("}");

        return s.toString();
    }

    private static String GetCppContent(final ClassDesc Desc)
    {
        final StringJoiner s = new StringJoiner(System.lineSeparator());

        s.add("");
        s.add("#include \"ConstantPool/" + Desc.GetFullName() + ".h\"");
        s.add("#include \"MemoryFile.h\"");
        s.add("");
        s.add("#include <sstream>");
        s.add("");

        // Namespace enter
        s.add("namespace " + Const.GenNamespace);
        s.add("{");

        // ToString()
        s.add("    std::string C" + Desc.GetFullName() + "::ToString() const");
        s.add("    {");
        s.add("        std::ostringstream oss;");
        s.add("        oss << \"" + Desc.GetFullName() + " {\" << std::endl;");
        for (final Pair<String, String> Pair : Desc)
        {
        s.add("        oss << " + String.format("\"%20s: \" << %s << std::endl;", Pair.Second, Pair.Second));
        }
        s.add("        oss << \"}\" << std::endl;");
        s.add("        return std::move(oss.str());");
        s.add("    }");
        s.add("");


        // Deserialize method
        s.add("    void C" + Desc.GetFullName() + "::" + Const.GenDeserializeMethod + "(" + Const.GenReaderNamespace + "::C" + Const.GenReaderClass + "& Reader)");
        s.add("    {");
        for (final Pair<String, String> Pair : Desc)
        {
        s.add("        Reader >> " + Pair.Second + ";");
        }
        s.add("    }");
        s.add("");

        // operator>>()
        s.add("    void operator>>(" + Const.GenReaderNamespace + "::C" + Const.GenReaderClass + "& Reader, C" + Desc.GetFullName() + "& Instance)");
        s.add("    {");
        s.add("        Instance." + Const.GenDeserializeMethod + "(Reader);");
        s.add("    }");

        // Namespace exit
        s.add("}");

        return s.toString();
    }

    public static void main(String[] args) throws Exception
    {
        final List<ClassDesc> ClassDescriptions = Arrays.asList(
            new ClassDesc("Class", Collections.singletonList(
                Pair.of("u2", "NameIndex")
            )),
            new ClassDesc("FieldRef", Arrays.asList(
                Pair.of("u2", "ClassIndex"),
                Pair.of("u2", "NameAndTypeIndex")
            )),
            new ClassDesc("MethodRef", Arrays.asList(
                Pair.of("u2", "ClassIndex"),
                Pair.of("u2", "NameAndTypeIndex")
            )),
            new ClassDesc("InterfaceMethodRef", Arrays.asList(
                Pair.of("u2", "ClassIndex"),
                Pair.of("u2", "NameAndTypeIndex")
            )),
            new ClassDesc("String", Collections.singletonList(
                Pair.of("u2", "StringIndex")
            )),
            new ClassDesc("Integer", Collections.singletonList(
                Pair.of("u4", "Bytes")
            )),
            new ClassDesc("Float", Collections.singletonList(
                Pair.of("u4", "Bytes")
            )),
            new ClassDesc("Long", Arrays.asList(
                Pair.of("u4", "HighBytes"),
                Pair.of("u4", "LowBytes")
            )),
            new ClassDesc("Double", Arrays.asList(
                Pair.of("u4", "HighBytes"),
                Pair.of("u4", "LowBytes")
            )),
            new ClassDesc("NameAndType", Arrays.asList(
                Pair.of("u2", "NameIndex"),
                Pair.of("u2", "DescriptorIndex")
            )),
            new ClassDesc("Utf8", Arrays.asList(
                Pair.of("u2", "Length"),
                Pair.of("u1*", "Bytes")
            )),
            new ClassDesc("MethodHandle", Arrays.asList(
                Pair.of("u1", "ReferenceKind"),
                Pair.of("u2", "ReferenceIndex")
            )),
            new ClassDesc("MethodType", Collections.singletonList(
                Pair.of("u2", "DescriptorIndex")
            )),
            new ClassDesc("InvokeDynamic", Arrays.asList(
                Pair.of("u2", "BootstrapMethodAttrIndex"),
                Pair.of("u2", "NameAndTypeIndex")
            ))
        );

        final Path OutputDirectory = Paths.get("OutputDirectory");
        DeleteDir(OutputDirectory);

        final Path CppDirectory = OutputDirectory.resolve("Private");
        Files.createDirectories(CppDirectory);

        final Path HeadersDirectory = OutputDirectory.resolve("Public");
        Files.createDirectories(HeadersDirectory);

        for (final ClassDesc Desc : ClassDescriptions)
        {
            final File HeaderFile = HeadersDirectory.resolve(Desc.GetFullName() + ".h").toFile();
            final File CppFile = CppDirectory.resolve(Desc.GetFullName() + ".cpp").toFile();

            final String HeaderContent = GetHeaderContent(Desc);
            final String CppContent = GetCppContent(Desc);

            try (final OutputStream dos = new FileOutputStream(HeaderFile))
            {
                dos.write(HeaderContent.getBytes(StandardCharsets.UTF_8));
            }

            try (final OutputStream dos = new FileOutputStream(CppFile))
            {
                dos.write(CppContent.getBytes(StandardCharsets.UTF_8));
            }
        }
    }
}
