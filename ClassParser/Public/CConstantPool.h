//
// Created by ASUS on 27/12/2020.
//

#ifndef CPP20_CCONSTANTPOOL_H
#define CPP20_CCONSTANTPOOL_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include "Types.h"


#include "StringUtf8.h"


class ClassFileBlob
{
private:
    ClassFileBlob(const usz size);

public:
    ~ClassFileBlob();

    static ClassFileBlob* fromFile(const char* fileName);


    void read(uint8_t* bytes, usz numBytes);

    u1* GetBytes(usz NumBytes);



private:
    const usz _size;
    uint8_t* const _data;

    usz _index = 0;
};

void operator>>(ClassFileBlob& blob, u1& v);
void operator>>(ClassFileBlob& blob, u2& v);
void operator>>(ClassFileBlob& blob, u4& v);
void operator>>(ClassFileBlob& blob, u8& v);

enum class EConstantPoolInfoTag : u1
{
    // Note: They must be in the ascending order to make the binary search work
    Utf8                = 1,
    Integer             = 3,
    Float               = 4,
    Long                = 5,
    Double              = 6,
    Class               = 7,
    String              = 8,
    Fieldref            = 9,
    Methodref           = 10,
    InterfaceMethodref  = 11,
    NameAndType         = 12,
    MethodHandle        = 15,
    MethodType          = 16,
    InvokeDynamic       = 18,
};

namespace Parser
{
    EConstantPoolInfoTag GetConstantPoolInfoTag(u1 InTagByte);


}

class cp_info
{
    const u1 _tag;

public:
    FORCEINLINE cp_info(u1 tag) : _tag(tag)
    {
    }

    FORCEINLINE EConstantPoolInfoTag getTag() const
    {
        return (EConstantPoolInfoTag)_tag;
    }

    virtual std::string to_string() const = 0;
};

struct CONSTANT_Class_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 name_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Class_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};



struct CONSTANT_Fieldref_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 class_index;
    u2 name_and_type_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Fieldref_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_Methodref_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 class_index;
    u2 name_and_type_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Methodref_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_InterfaceMethodref_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 class_index;
    u2 name_and_type_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_InterfaceMethodref_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_String_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 string_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_String_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_Integer_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u4 bytes;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Integer_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_Float_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u4 bytes;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Float_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_Long_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u4 high_bytes;
    u4 low_bytes;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Long_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_Double_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u4 high_bytes;
    u4 low_bytes;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Double_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_NameAndType_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 name_index;
    u2 descriptor_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_NameAndType_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_Utf8_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    Util::StringUtf8 String;

    [[nodiscard]]
    FORCEINLINE const Util::StringUtf8& GetString() const
    {
        return String;
    }

    friend void operator>>(ClassFileBlob& blob, CONSTANT_Utf8_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_MethodHandle_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u1 reference_kind;
    u2 reference_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_MethodHandle_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_MethodType_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 descriptor_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_MethodType_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};

struct CONSTANT_InvokeDynamic_info : public cp_info
{
    using cp_info::cp_info;

    // u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;

    friend void operator>>(ClassFileBlob& blob, CONSTANT_InvokeDynamic_info& _this);

    std::string to_string() const override;

    static const EConstantPoolInfoTag StaticTag;
};




class CConstantPool
{
public:
    explicit FORCEINLINE CConstantPool(usz size = 0)
    {
        if (size > 0)
        {
            cp_infos.reserve(size);
        }
    }

    FORCEINLINE void Add(cp_info* info)
    {
        cp_infos.push_back(info);
    }

    template<class T>
    FORCEINLINE const T* Get(const usz index) const
    {
        static_assert(std::is_base_of<cp_info, T>::value, "T must be inherited from cp_info");

        if ((index > 0) && (index <= cp_infos.size()))
        {
            // OOB
        }

        if (cp_info* const info = cp_infos[index - 1])
        {
            if (info->getTag() == T::StaticTag)
            {
                return reinterpret_cast<T*>(info);
            }
            else
            {
                // check(incorrect type)
            }
        }

        return nullptr;
    }

    FORCEINLINE std::vector<cp_info*>::iterator begin() { return cp_infos.begin(); }
    FORCEINLINE std::vector<cp_info*>::iterator end() { return cp_infos.end(); }

private:
    std::vector<cp_info*> cp_infos;
};


#endif //CPP20_CCONSTANTPOOL_H
