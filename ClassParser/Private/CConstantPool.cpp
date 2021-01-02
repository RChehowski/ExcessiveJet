//
// Created by ASUS on 27/12/2020.
//

#include <cstdio>
#include <cstring>
#include <algorithm>
#include "CConstantPool.h"

#include "Platform/Misc.h"
#include "Assert.h"

constexpr EConstantPoolInfoTag ConstantPoolInfoTags[] =
{
    // Note: They must be in the ascending order to make the binary search work
    EConstantPoolInfoTag::Utf8,
    EConstantPoolInfoTag::Integer,
    EConstantPoolInfoTag::Float,
    EConstantPoolInfoTag::Long,
    EConstantPoolInfoTag::Double,
    EConstantPoolInfoTag::Class,
    EConstantPoolInfoTag::String,
    EConstantPoolInfoTag::Fieldref,
    EConstantPoolInfoTag::Methodref,
    EConstantPoolInfoTag::InterfaceMethodref,
    EConstantPoolInfoTag::NameAndType,
    EConstantPoolInfoTag::MethodHandle,
    EConstantPoolInfoTag::MethodType,
    EConstantPoolInfoTag::InvokeDynamic,
};

EConstantPoolInfoTag Parser::GetConstantPoolInfoTag(u1 InTagByte)
{
    const EConstantPoolInfoTag TagByteAsTag = (EConstantPoolInfoTag)InTagByte;
    
    // Validate the tag byte
    bool bTagIsValid = std::binary_search(
        std::begin(ConstantPoolInfoTags),
        std::end(ConstantPoolInfoTags),
        TagByteAsTag
    );
    ASSERT(bTagIsValid);

    return TagByteAsTag;
}



ClassFileBlob::ClassFileBlob(const usz size) : _size(size), _data((uint8_t*)malloc(_size))
{
}

ClassFileBlob::~ClassFileBlob()
{

}

ClassFileBlob* ClassFileBlob::fromFile(const char* fileName)
{
    FILE* file;
    fopen_s(&file, fileName, "rb");

    fseek(file, 0, SEEK_END);
    const usz fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    ClassFileBlob* const classFileBlob = new ClassFileBlob(fileSize);
    fread(classFileBlob->_data, classFileBlob->_size, 1, file);
    fclose(file);

    return classFileBlob;
}

void ClassFileBlob::read(uint8_t* bytes, usz numBytes)
{
    const uint8_t* const readPtr = _data + _index;
    _index += numBytes;

    memcpy(bytes, readPtr, numBytes);
}

u1* ClassFileBlob::GetBytes(usz NumBytes)
{
    u1* const ReadPtr = _data + _index;
    _index += NumBytes;

    return ReadPtr;
}


void operator>>(ClassFileBlob& blob, u1& v)
{
    u1 temp;
    blob.read((uint8_t*)&temp, sizeof(temp));
    v = Util::BigEndianToNative(temp);
}

void operator>>(ClassFileBlob& blob, u2& v)
{
    u2 temp;
    blob.read((uint8_t*)&temp, sizeof(temp));
    v = Util::BigEndianToNative(temp);
}

void operator>>(ClassFileBlob& blob, u4& v)
{
    u4 temp;
    blob.read((uint8_t*)&temp, sizeof(temp));
    v = Util::BigEndianToNative(temp);
}

void operator>>(ClassFileBlob& blob, u8& v)
{
    u8 temp;
    blob.read((uint8_t*)&temp, sizeof(temp));
    v = Util::BigEndianToNative(temp);
}


void operator>>(ClassFileBlob& blob, CONSTANT_Class_info& _this)
{
    blob >> _this.name_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Fieldref_info& _this)
{
    blob >> _this.class_index;
    blob >> _this.name_and_type_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Methodref_info& _this)
{
    blob >> _this.class_index;
    blob >> _this.name_and_type_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_InterfaceMethodref_info& _this)
{
    blob >> _this.class_index;
    blob >> _this.name_and_type_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_String_info& _this)
{
    blob >> _this.string_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Integer_info& _this)
{
    blob >> _this.bytes;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Float_info& _this)
{
    blob >> _this.bytes;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Long_info& _this)
{
    blob >> _this.high_bytes;
    blob >> _this.low_bytes;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Double_info& _this)
{
    blob >> _this.high_bytes;
    blob >> _this.low_bytes;
}

void operator>>(ClassFileBlob& blob, CONSTANT_NameAndType_info& _this)
{
    blob >> _this.name_index;
    blob >> _this.descriptor_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_Utf8_info& _this)
{
    u2 NumBytes = 0;
    blob >> NumBytes;

    u1* Data = blob.GetBytes(NumBytes);
    _this.String = std::move(Util::StringUtf8(Data, NumBytes));
}

void operator>>(ClassFileBlob& blob, CONSTANT_MethodHandle_info& _this)
{
    blob >> _this.reference_kind;
    blob >> _this.reference_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_MethodType_info& _this)
{
    blob >> _this.descriptor_index;
}

void operator>>(ClassFileBlob& blob, CONSTANT_InvokeDynamic_info& _this)
{
    blob >> _this.bootstrap_method_attr_index;
    blob >> _this.name_and_type_index;
}


std::string CONSTANT_Class_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Class_info {" << std::endl;
    oss << "  name_index: " << name_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Fieldref_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Fieldref_info {" << std::endl;
    oss << "  class_index: " << class_index << std::endl;
    oss << "  name_and_type_index: " << name_and_type_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Methodref_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Fieldref_info {" << std::endl;
    oss << "  class_index: " << class_index << std::endl;
    oss << "  name_and_type_index: " << name_and_type_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_InterfaceMethodref_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_InterfaceMethodref_info {" << std::endl;
    oss << "  class_index: " << class_index << std::endl;
    oss << "  name_and_type_index: " << name_and_type_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_String_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_String_info {" << std::endl;
    oss << "  string_index: " << string_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Integer_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Integer_info {" << std::endl;
    oss << "  bytes: " << bytes << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Float_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Float_info {" << std::endl;
    oss << "  bytes: " << bytes << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Long_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Long_info {" << std::endl;
    oss << "  high_bytes: " << high_bytes << std::endl;
    oss << "  low_bytes : " << low_bytes << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Double_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Double_info {" << std::endl;
    oss << "  high_bytes: " << high_bytes << std::endl;
    oss << "  low_bytes : " << low_bytes << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_NameAndType_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_NameAndType_info {" << std::endl;
    oss << "  name_index      : " << name_index << std::endl;
    oss << "  descriptor_index: " << descriptor_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_Utf8_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_Utf8_info {" << std::endl;
    oss << "  length: " << String.GetNumBytes() << std::endl;
    oss << "  bytes: " << (std::string)String << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_MethodHandle_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_MethodHandle_info {" << std::endl;
    oss << "  reference_kind : " << reference_kind << std::endl;
    oss << "  reference_index: " << reference_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_MethodType_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_MethodHandle_info {" << std::endl;
    oss << "  descriptor_index: " << descriptor_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

std::string CONSTANT_InvokeDynamic_info::to_string() const
{
#if STRIP_DEBUG_INFO
    return "";
#else
    std::ostringstream oss;

    oss << "CONSTANT_InvokeDynamic_info {" << std::endl;
    oss << "  bootstrap_method_attr_index: " << bootstrap_method_attr_index << std::endl;
    oss << "  name_and_type_index        : " << name_and_type_index << std::endl;
    oss << "}" << std::endl;

    return std::move(oss.str());
#endif // STRIP_DEBUG_INFO
}

// StaticTag
const EConstantPoolInfoTag CONSTANT_Class_info::StaticTag = EConstantPoolInfoTag::Class;
const EConstantPoolInfoTag CONSTANT_Fieldref_info::StaticTag = EConstantPoolInfoTag::Fieldref;
const EConstantPoolInfoTag CONSTANT_Methodref_info::StaticTag = EConstantPoolInfoTag::Methodref;
const EConstantPoolInfoTag CONSTANT_InterfaceMethodref_info::StaticTag = EConstantPoolInfoTag::InterfaceMethodref;
const EConstantPoolInfoTag CONSTANT_String_info::StaticTag = EConstantPoolInfoTag::String;
const EConstantPoolInfoTag CONSTANT_Integer_info::StaticTag = EConstantPoolInfoTag::Integer;
const EConstantPoolInfoTag CONSTANT_Float_info::StaticTag = EConstantPoolInfoTag::Float;
const EConstantPoolInfoTag CONSTANT_Long_info::StaticTag = EConstantPoolInfoTag::Long;
const EConstantPoolInfoTag CONSTANT_Double_info::StaticTag = EConstantPoolInfoTag::Double;
const EConstantPoolInfoTag CONSTANT_NameAndType_info::StaticTag = EConstantPoolInfoTag::NameAndType;
const EConstantPoolInfoTag CONSTANT_Utf8_info::StaticTag = EConstantPoolInfoTag::Utf8;
const EConstantPoolInfoTag CONSTANT_MethodHandle_info::StaticTag = EConstantPoolInfoTag::MethodHandle;
const EConstantPoolInfoTag CONSTANT_MethodType_info::StaticTag = EConstantPoolInfoTag::MethodType;
const EConstantPoolInfoTag CONSTANT_InvokeDynamic_info::StaticTag = EConstantPoolInfoTag::InvokeDynamic;

