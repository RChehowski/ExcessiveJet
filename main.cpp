
#include <stdint.h>
#include <cinttypes>

#include <cassert>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <intrin.h>
#include "ConstantPool.h"


//
//struct cp_info {
//    uint8_t tag;
//    uint8_t* info;
//}
//
//struct gemini_class_file
//{
//    uint64_t            magic;
//    uint16_t            minor_version;
//    uint16_t            major_version;
//    uint16_t            constant_pool_count;
//    cp_info        constant_pool[constant_pool_count-1];
//    uint16_t             access_flags;
//    uint16_t             this_class;
//    uint16_t             super_class;
//    uint16_t             interfaces_count;
//    uint16_t*             interfaces[interfaces_count];
//    uint16_t             fields_count;
//    field_info     fields[fields_count];
//    uint16_t             methods_count;
//    method_info    methods[methods_count];
//    uint16_t             attributes_count;
//    attribute_info attributes[attributes_count];
//};


#include <iostream>

//struct attribute_info
//{
//    u2 attribute_name_index;
//    u4 attribute_length;
//    u1 info[attribute_length];
//};

ConstantPool G_constant_pool;

struct AttributeInfo
{
    u2 attribute_name_index;
    u4 attribute_length;
//    u1 info[attribute_length];

    friend void operator>> (ClassFileBlob& blob, AttributeInfo& _this);
};


class ConstantUtf8View
{
    friend class std::hash<ConstantUtf8View>;

public:
    FORCEINLINE ConstantUtf8View(const u2 in_length, const u1* const in_bytes)
        : length(in_length)
        , bytes(in_bytes)
    {
    }

    FORCEINLINE bool operator==(const ConstantUtf8View& constant_utf8_view) const
    {
        if (length == constant_utf8_view.length)
        {
            for (u2 i = 0; i < length; ++i)
            {
                if (bytes[i] != constant_utf8_view.bytes[i])
                {
                    return false;
                }
            }

            return false;
        }
        else
        {
            return false;
        }
    }

protected:
    u2 length;
    const u1* bytes;
};

class LiteralConstantUtf8View : public ConstantUtf8View
{
    FORCEINLINE u1* string_to_bytes(const std::string& in_string)
    {
        u1* const bytes = (u1*)malloc(in_string.length());
        memcpy(bytes, in_string.c_str(), in_string.length());

        return bytes;
    }

public:
    FORCEINLINE LiteralConstantUtf8View(const std::string& in_string)
        : ConstantUtf8View(in_string.length(), string_to_bytes(in_string))
    {
        puts("");
    }

    LiteralConstantUtf8View(const LiteralConstantUtf8View& other) : ConstantUtf8View(0, nullptr)
    {
        length = other.length;

        bytes = (u1*)malloc((usz)length);
        memcpy((void*)bytes, (const void*)other.bytes, (usz)length);
    }

//    LiteralConstantUtf8View(LiteralConstantUtf8View&& other) noexcept :
//            ConstantUtf8View(other.length, other.bytes)
//    {
//        other.length = 0;
//        other.bytes = nullptr;
//    }

    FORCEINLINE ~LiteralConstantUtf8View()
    {
        if (bytes)
        {
            free((void *)bytes);
        }
    }
};

namespace std
{
    template<>
    struct hash<ConstantUtf8View> {
        std::size_t operator()(const ConstantUtf8View &constant_utf8_view) const {
            size_t result = 0;
            const size_t prime = 31;

            for (u2 i = 0; i < constant_utf8_view.length; ++i) {
                result = constant_utf8_view.bytes[i] + (result * prime);
            }

            return result;
        }
    };
}





void read_attribute_Deprecated(ClassFileBlob& blob, u2 attribute_name_index, u4 attribute_length) noexcept
{
    std::cout << "read_attribute_Deprecated";
}

void read_attribute_RuntimeVisibleAnnotations(ClassFileBlob& blob, u2 attribute_name_index, u4 attribute_length) noexcept
{
    u2 NumAnnotations = (u2)0;
    blob >> NumAnnotations;

    for (u2 AnnotationIndex = 0; AnnotationIndex < NumAnnotations; ++AnnotationIndex)
    {
        u2 TypeIndex = (u2)0;
        blob >> TypeIndex;

        u2 NumElementValuePairs = (u2)0;
        blob >> NumElementValuePairs;

        for (u2 ElementValuePairsIndex = 0; ElementValuePairsIndex < NumElementValuePairs; ++ElementValuePairsIndex)
        {
            u2 ElementNameIndex = (u2)0;
            blob >> ElementNameIndex;

            u1 Tag = (u1)0;
            blob >> Tag;

            switch ((char)Tag)
            {
                case 'B':
                case 'C':
                case 'D':
                case 'F':
                case 'I':
                case 'J':
                case 'S':
                case 'Z':
                case 's': // String
                {
                    u2 ConstValueIndex = (u2)0;
                    blob >> ConstValueIndex;

                    break;
                }
                case 'e': // enum constant
                {
                    u2 TypeNameIndex = (u2)0;
                    blob >> TypeNameIndex;

                    u2 ConstNameIndex = (u2)0;
                    blob >> ConstNameIndex;

                    break;
                }
                case 'c': // class
                {
                    u2 ClassInfoIndex = (u2)0;
                    blob >> ClassInfoIndex;

                    break;
                }
                case '@': // annotation type
                {
                    // TODO: Add support

                    break;
                }
                case '[': // array
                {
                    // TODO: Add support

                    break;
                }
            }
        }
    }
}

#include "Opcodes.h"

using Bytecode::Opcodes;

void read_attribute_Code(ClassFileBlob& blob, u2 attribute_name_index, u4 attribute_length) noexcept
{
    u2 MaxStack = (u2)0;
    blob >> MaxStack;

    u2 MaxLocals = (u2)0;
    blob >> MaxLocals;

    u4 CodeLength = (u4)0;
    blob >> CodeLength;

    u1* Code = Util::Memory::MallocT<u1>((usz)CodeLength);
    Util::Memory::Memcpy(Code, blob.GetBytes(CodeLength), CodeLength);

    std::ostringstream oss;
    for (u4 i = 0; i < CodeLength; ++i)
    {
        const Bytecode::Opcode& Opcode = Bytecode::GetOpcodeForByte(Code[i]);
        std::cout << Opcode.ToString() << std::endl;

        const u1* CodePoint = Code + i + 1;

        switch (Opcode.GetOperation())
        {
            case Opcodes::ALOAD.GetOperation():
            {
                break;
            }
            case Opcodes::INVOKESPECIAL.GetOperation():
            {
                const u2 ConstantPoolIndex = (((u2)CodePoint[0] << 8) & 0xFF00 | (u2)CodePoint[1] & 0x00FF);

                i += 2;
                break;
            }
            case Opcodes::LDC.GetOperation():
            {
                const u2 ConstantPoolIndex = (u2)CodePoint[0] & 0x00FF;

                i += 1;
                break;
            }
            case Opcodes::PUTFIELD.GetOperation():
            {
                const u2 ConstantPoolIndex = (((u2)CodePoint[0] << 8) & 0xFF00 | (u2)CodePoint[1] & 0x00FF);

                i += 2;
                break;
            }
        }
    }
    std::string Result = oss.str();

    u2 ExceptionTableLength = (u2)0;
    blob >> ExceptionTableLength;

    for (u2 ExceptionTableIndex = 0; ExceptionTableIndex < ExceptionTableLength; ExceptionTableLength++)
    {
        u2 StartPc = (u2)0;
        blob >> StartPc;

        u2 EndPc = (u2)0;
        blob >> EndPc;

        u2 HandlerPc = (u2)0;
        blob >> HandlerPc;

        u2 CatchType = (u2)0;
        blob >> CatchType;
    }

    u2 AttributesCount = (u2)0;
    blob >> AttributesCount;

    for (u2 AttributeIndex = 0; AttributeIndex < AttributesCount; ++AttributeIndex)
    {
        AttributeInfo Info;
        blob >> Info;
    }

    std::cout << "func_ret";
}

void read_attribute_LineNumberTable(ClassFileBlob& blob, u2 attribute_name_index, u4 attribute_length) noexcept
{
    u2 LineNumberTableLength = (u2)0;
    blob >> LineNumberTableLength;

    for (u2 LineNumberTableIndex = 0; LineNumberTableIndex < LineNumberTableLength; ++LineNumberTableIndex)
    {
        u2 StartPc = (u2)0;
        blob >> StartPc;

        u2 LineNumber = (u2)0;
        blob >> LineNumber;
    }
}

void read_attribute_LocalVariableTable(ClassFileBlob& blob, u2 attribute_name_index, u4 attribute_length) noexcept
{
    u2 LocalVariableTableLength = (u2)0;
    blob >> LocalVariableTableLength;

    for (u2 LocalVariableTableIndex = 0; LocalVariableTableIndex < LocalVariableTableLength; ++LocalVariableTableIndex)
    {
        u2 StartPc = (u2)0;
        blob >> StartPc;

        u2 Length = (u2)0;
        blob >> Length;

        u2 NameIndex = (u2)0;
        blob >> NameIndex;

        u2 DescriptorIndex = (u2)0;
        blob >> DescriptorIndex;

        u2 Index = (u2)0;
        blob >> Index;
    }
}

#include "Attributes.h"

//typedef void (*ReadFunction)(ClassFileBlob&, u2, u4);
//typedef std::unordered_map<Parser::CAttributeName, ReadFunction> FuncMap;


//const FuncMap G_Map({
//    {
//        Parser::CAttributeNames::Deprecated,
//        read_attribute_Deprecated
//    }
//    {
//        "RuntimeVisibleAnnotations",
//        read_attribute_RuntimeVisibleAnnotations
//    },
//    {
//        "Code",
//        read_attribute_Code
//    },
//    {
//        "LineNumberTable",
//        read_attribute_LineNumberTable
//    },
//    {
//        "LocalVariableTable",
//        read_attribute_LocalVariableTable
//    }
//});

void operator>> (ClassFileBlob& blob, AttributeInfo& _this)
{
    blob >> _this.attribute_name_index;
    blob >> _this.attribute_length;

//    CONSTANT_Utf8_info* utf8_info = G_constant_pool.Get<CONSTANT_Utf8_info>(_this.attribute_name_index);

//    auto It = G_Map.find(utf8_info->GetString());
//    if (It != G_Map.end())
//    {
//        It->second(blob, _this.attribute_name_index, _this.attribute_length);
//    }
}

struct FieldInfo
{
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
//    attribute_info attributes[attributes_count];

    FieldInfo() = default;

    friend void operator>> (ClassFileBlob& blob, FieldInfo& _this);
};

struct MethodInfo
{
    u2             access_flags;
    u2             name_index;
    u2             descriptor_index;
    u2             attributes_count;
//    attribute_info attributes[attributes_count];

    MethodInfo() = default;

    friend void operator>> (ClassFileBlob& blob, MethodInfo& _this);
};

void operator>> (ClassFileBlob& blob, FieldInfo& _this)
{
    blob >> _this.access_flags;
    blob >> _this.name_index;
    blob >> _this.descriptor_index;
    blob >> _this.attributes_count;

    for (u2 attribute_index = 0; attribute_index < _this.attributes_count; ++attribute_index)
    {
        AttributeInfo attribute_info;
        blob >> attribute_info;
    }
}

void operator>> (ClassFileBlob& blob, MethodInfo& _this)
{
    blob >> _this.access_flags;
    blob >> _this.name_index;
    blob >> _this.descriptor_index;
    blob >> _this.attributes_count;

    for (u2 attribute_index = 0; attribute_index < _this.attributes_count; ++attribute_index)
    {
        AttributeInfo attribute_info;
        blob >> attribute_info;
    }
}









int main()
{
    const char* classFileName = "C:\\Users\\ASUS\\Projects\\JavaHello\\out\\production\\JavaHello\\com\\company\\Sample.class";

    ClassFileBlob* classFileBlob = ClassFileBlob::fromFile(classFileName);

    uint32_t magic;
    (*classFileBlob) >> magic;

    uint16_t minor_version;
    (*classFileBlob) >> minor_version;

    uint16_t major_version;
    (*classFileBlob) >> major_version;

    uint16_t constant_pool_count;
    (*classFileBlob) >> constant_pool_count;


    for (u2 constant_pool_index = 1; constant_pool_index < constant_pool_count; ++constant_pool_index)
    {
        std::cout << " >> " << (int)constant_pool_index << " >> " << std::endl;

        u1 tag;
        (*classFileBlob) >> tag;

        switch((EConstantPoolInfoTag)tag)
        {
            case EConstantPoolInfoTag::Class:
            {
                CONSTANT_Class_info* const const_info = new CONSTANT_Class_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Fieldref:
            {
                CONSTANT_Fieldref_info* const const_info = new CONSTANT_Fieldref_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Methodref:
            {
                CONSTANT_Methodref_info* const const_info = new CONSTANT_Methodref_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::InterfaceMethodref:
            {
                CONSTANT_InterfaceMethodref_info* const const_info = new CONSTANT_InterfaceMethodref_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::String:
            {
                CONSTANT_String_info* const const_info = new CONSTANT_String_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Integer:
            {
                CONSTANT_Integer_info* const const_info = new CONSTANT_Integer_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Float:
            {
                CONSTANT_Float_info* const const_info = new CONSTANT_Float_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Long:
            {
                CONSTANT_Long_info* const const_info = new CONSTANT_Long_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Double:
            {
                CONSTANT_Double_info* const const_info = new CONSTANT_Double_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::NameAndType:
            {
                CONSTANT_NameAndType_info* const const_info = new CONSTANT_NameAndType_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::Utf8:
            {
                CONSTANT_Utf8_info* const const_info = new CONSTANT_Utf8_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::MethodHandle:
            {
                CONSTANT_MethodHandle_info* const const_info = new CONSTANT_MethodHandle_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::MethodType:
            {
                CONSTANT_MethodType_info* const const_info = new CONSTANT_MethodType_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            case EConstantPoolInfoTag::InvokeDynamic:
            {
                CONSTANT_InvokeDynamic_info* const const_info = new CONSTANT_InvokeDynamic_info(tag);
                *(classFileBlob) >> *const_info;
                G_constant_pool.Add(const_info);

                break;
            }
            default:
            {
                exit(tag);
            }
        }
    }

    int i = 1;
    for (const cp_info* const info : G_constant_pool)
    {
        std::cout << i++ << ")" << info->to_string() << std::endl;
    }
    u2 access_flags;
    (*classFileBlob) >> access_flags;

    u2 this_class;
    (*classFileBlob) >> this_class;

    u2 super_class;
    (*classFileBlob) >> super_class;

    u2 interfaces_count;
    (*classFileBlob) >> interfaces_count;

    u2* interfaces = (interfaces_count == 0) ? nullptr : (u2*)malloc((usz)interfaces_count);
    for (u2 interface_index = 0; interface_index < interfaces_count; ++interface_index)
    {
        (*classFileBlob) >> interfaces[interface_index];
    }

    u2 fields_count;
    (*classFileBlob) >> fields_count;

    for (u2 field_index = 0; field_index < fields_count; ++field_index)
    {
        FieldInfo field_info;
        (*classFileBlob) >> field_info;
    }

    u2 MethodsCount;
    (*classFileBlob) >> MethodsCount;

    for (u2 MethodIndex = 0; MethodIndex < MethodsCount; ++MethodIndex)
    {
        MethodInfo method_info;
        (*classFileBlob) >> method_info;
    }

    printf("0x%x\n", magic);

    return 0;
}
