//
// Created by ASUS on 27/12/2020.
//

#include <cstdio>
#include <cstring>
#include "ConstantPool.h"

#include "Platform/Misc.h"

ClassFileBlob::ClassFileBlob(const size_t size) : _size(size), _data((uint8_t*)malloc(_size))
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
    const size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    ClassFileBlob* const classFileBlob = new ClassFileBlob(fileSize);
    fread(classFileBlob->_data, classFileBlob->_size, 1, file);
    fclose(file);

    return classFileBlob;
}

void ClassFileBlob::read(uint8_t* bytes, size_t numBytes)
{
    const uint8_t* const readPtr = _data + _index;
    _index += numBytes;

    memcpy(bytes, readPtr, numBytes);
}

u1* ClassFileBlob::GetBytes(size_t NumBytes)
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
const ConstantPoolInfoTag CONSTANT_Class_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Class;
const ConstantPoolInfoTag CONSTANT_Fieldref_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Fieldref;
const ConstantPoolInfoTag CONSTANT_Methodref_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Methodref;
const ConstantPoolInfoTag CONSTANT_InterfaceMethodref_info::StaticTag = ConstantPoolInfoTag::CONSTANT_InterfaceMethodref;
const ConstantPoolInfoTag CONSTANT_String_info::StaticTag = ConstantPoolInfoTag::CONSTANT_String;
const ConstantPoolInfoTag CONSTANT_Integer_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Integer;
const ConstantPoolInfoTag CONSTANT_Float_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Float;
const ConstantPoolInfoTag CONSTANT_Long_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Long;
const ConstantPoolInfoTag CONSTANT_Double_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Double;
const ConstantPoolInfoTag CONSTANT_NameAndType_info::StaticTag = ConstantPoolInfoTag::CONSTANT_NameAndType;
const ConstantPoolInfoTag CONSTANT_Utf8_info::StaticTag = ConstantPoolInfoTag::CONSTANT_Utf8;
const ConstantPoolInfoTag CONSTANT_MethodHandle_info::StaticTag = ConstantPoolInfoTag::CONSTANT_MethodHandle;
const ConstantPoolInfoTag CONSTANT_MethodType_info::StaticTag = ConstantPoolInfoTag::CONSTANT_MethodType;
const ConstantPoolInfoTag CONSTANT_InvokeDynamic_info::StaticTag = ConstantPoolInfoTag::CONSTANT_InvokeDynamic;

