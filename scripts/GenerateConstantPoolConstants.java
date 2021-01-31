import java.io.*;
import java.util.*;

public class GenerateConstantPoolConstants
{
    private static String GetHungarianClassName(final String ClassName)
    {
        return 'C' + ClassName;
    }

    /**
     * Java 5 has no StringJoiner
     */
    private static class NewLineJoiner
    {
        private NewLineJoiner add(Object object)
        {
            Strings.add(object.toString());
            return this;
        }

        @Override
        public String toString()
        {
            final StringBuilder sb = new StringBuilder();

            final int Size = Strings.size();
            for (int i = 0; i < Size; i++)
            {
                sb.append(Strings.get(i));
                if (i < (Size - 1))
                {
                    sb.append("\n");
                }
            }

            return sb.toString();
        }

        private List<String> Strings = new ArrayList<String>();
    }

    private static class Const
    {
        private static final String GenNamespace = "Parse";

        private static final String GenReaderClass = "ClassReader";
        private static final String GenBaseClass = "ConstantInfo";

        private static final String GenDeserializeMethod = "DeserializeFrom";
    }

    private static class Pair<TFirst, TSecond>
    {
        private final TFirst First;
        private final TSecond Second;

        private Pair(TFirst first, TSecond second)
        {
            First = first;
            Second = second;
        }

        private static<TFirst, TSecond> Pair<TFirst, TSecond> Of(TFirst First, TSecond Second)
        {
            return new Pair<TFirst, TSecond>(First, Second);
        }
    }

    private static class ClassDesc implements Iterable<Pair<String, String>>
    {
        private final String Name;
        private final List<Pair<String, String>> Fields;

        private ClassDesc(final String InName, final Pair<String, String>... InFields)
        {
            Name = InName;

            Fields = new ArrayList<Pair<String, String>>(InFields.length);
            Collections.addAll(Fields, InFields);
        }

        public Iterator<Pair<String, String>> iterator()
        {
            return Fields.iterator();
        }

        private String GetFullName()
        {
            return "Constant" + Name + "Info";
        }
    }

    private static void DeleteDir(final File DirFile) throws IOException
    {
        assert DirFile != null;

        if (DirFile.isDirectory())
        {
            final File[] FilesInDirectory = DirFile.listFiles();
            if (FilesInDirectory != null)
            {
                for (File FileInDirectory : FilesInDirectory)
                {
                    if (FileInDirectory.isDirectory())
                    {
                        // Recurse
                        DeleteDir(FileInDirectory);
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
            assert DirFile.delete();
        }
    }

    private static String GetHeaderContent(final ClassDesc Desc)
    {
        final NewLineJoiner s = new NewLineJoiner();

        s.add("#pragma once");
        s.add("");
        s.add("#include \"ConstantPool/" + Const.GenBaseClass + ".h\"");
        s.add("");

        s.add("namespace " + Const.GenNamespace);
        s.add("{");
        s.add("    class " + GetHungarianClassName(Const.GenReaderClass) + ";");
        s.add("    ");
        s.add("    class " + GetHungarianClassName(Desc.GetFullName()) + " : public " + GetHungarianClassName(Const.GenBaseClass));
        s.add("    {");
        s.add("    public:");

        // Inherited constructor
        s.add("        using " + GetHungarianClassName(Const.GenBaseClass) + "::" + GetHungarianClassName(Const.GenBaseClass) + ";");
        s.add("");

        // ToString()
        s.add("        [[nodiscard]]");
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
        s.add("        void " + Const.GenDeserializeMethod + "(" + GetHungarianClassName(Const.GenReaderClass) + "& Reader) override;");
        s.add("");

        // Operator>>
        s.add("        friend void operator>>(" + GetHungarianClassName(Const.GenReaderClass) + "& Reader, " + GetHungarianClassName(Desc.GetFullName()) + "& Instance);");
        s.add("");


        // Static fields
        s.add("    public:");
        s.add("        static constexpr EConstantPoolInfoTag StaticTag = EConstantPoolInfoTag::" + Desc.Name + ";");
        s.add("");

        // Instance fields
        s.add("    private:");
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
        final NewLineJoiner s = new NewLineJoiner();

        s.add("");
        s.add("#include \"ConstantPool/" + Desc.GetFullName() + ".h\"");
        s.add("#include \"ClassReader.h\"");
        s.add("");
        s.add("#include <sstream>");
        s.add("");

        // Namespace enter
        s.add("namespace " + Const.GenNamespace);
        s.add("{");

        // ToString()
        s.add("    std::string " + GetHungarianClassName(Desc.GetFullName()) + "::ToString() const");
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
        s.add("    void " + GetHungarianClassName(Desc.GetFullName()) + "::" + Const.GenDeserializeMethod + "(" + GetHungarianClassName(Const.GenReaderClass) + "& Reader)");
        s.add("    {");
        for (final Pair<String, String> Pair : Desc)
        {
        s.add("        Reader >> " + Pair.Second + ";");
        }
        s.add("    }");
        s.add("");

        // operator>>()
        s.add("    void operator>>(" + GetHungarianClassName(Const.GenReaderClass) + "& Reader, " + GetHungarianClassName(Desc.GetFullName()) + "& Instance)");
        s.add("    {");
        s.add("        Instance." + Const.GenDeserializeMethod + "(Reader);");
        s.add("    }");
        s.add("");

        // Namespace exit
        s.add("}");

        return s.toString();
    }

    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws Exception
    {
        final List<ClassDesc> ClassDescriptions = Arrays.asList(
            new ClassDesc("Class",
                Pair.Of("u2", "NameIndex")
            ),
            new ClassDesc("FieldRef",
                Pair.Of("u2", "ClassIndex"),
                Pair.Of("u2", "NameAndTypeIndex")
            ),
            new ClassDesc("MethodRef",
                Pair.Of("u2", "ClassIndex"),
                Pair.Of("u2", "NameAndTypeIndex")
            ),
            new ClassDesc("InterfaceMethodRef",
                Pair.Of("u2", "ClassIndex"),
                Pair.Of("u2", "NameAndTypeIndex")
            ),
            new ClassDesc("String",
                Pair.Of("u2", "StringIndex")
            ),
            new ClassDesc("Integer",
                Pair.Of("u4", "Bytes")
            ),
            new ClassDesc("Float",
                Pair.Of("u4", "Bytes")
            ),
            new ClassDesc("Long",
                Pair.Of("u4", "HighBytes"),
                Pair.Of("u4", "LowBytes")
            ),
            new ClassDesc("Double",
                Pair.Of("u4", "HighBytes"),
                Pair.Of("u4", "LowBytes")
            ),
            new ClassDesc("NameAndType",
                Pair.Of("u2", "NameIndex"),
                Pair.Of("u2", "DescriptorIndex")
            ),
            new ClassDesc("Utf8",
                Pair.Of("Util::CStringUtf8", "StringUtf8")
            ),
            new ClassDesc("MethodHandle",
                Pair.Of("u1", "ReferenceKind"),
                Pair.Of("u2", "ReferenceIndex")
            ),
            new ClassDesc("MethodType",
                Pair.Of("u2", "DescriptorIndex")
            ),
            new ClassDesc("InvokeDynamic",
                Pair.Of("u2", "BootstrapMethodAttrIndex"),
                Pair.Of("u2", "NameAndTypeIndex")
            )
        );

        final File OutputDirectory = new File("OutputDirectory").getAbsoluteFile();
        DeleteDir(OutputDirectory);

        final File CppDirectory = new File(OutputDirectory, "Private");
        CppDirectory.mkdirs();

        final File HeadersDirectory = new File(OutputDirectory, "Public");
        HeadersDirectory.mkdirs();

        for (final ClassDesc Desc : ClassDescriptions)
        {
            final File HeaderFile = new File(HeadersDirectory, Desc.GetFullName() + ".h");
            HeaderFile.createNewFile();

            final File CppFile = new File(CppDirectory, Desc.GetFullName() + ".cpp");
            CppFile.createNewFile();

            final String HeaderContent = GetHeaderContent(Desc);
            final String CppContent = GetCppContent(Desc);

            {
                final OutputStream dos = new FileOutputStream(HeaderFile);
                dos.write(HeaderContent.getBytes("utf-8"));
                dos.close();
            }
            {
                final OutputStream dos = new FileOutputStream(CppFile);
                dos.write(CppContent.getBytes("utf-8"));
                dos.close();
            }
        }
    }
}
