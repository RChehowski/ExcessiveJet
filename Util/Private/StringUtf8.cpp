//
// Created by ASUS on 30/12/2020.
//

#include "StringUtf8.h"

namespace Util
{
    StringUtf8::StringUtf8() : StringUtf8(nullptr, (usz)0)
    {

    }

    StringUtf8::StringUtf8(const u1* const InData, const usz InNumBytes) : NumBytes(InNumBytes)
    {
        if (NumBytes > 0)
        {
            Data = Memory::MallocT<std::remove_pointer<decltype(Data)>::type>(NumBytes);
            Memory::Memcpy(Data, InData, NumBytes);
        }
        else
        {
            Data = nullptr;
        }
    }

    StringUtf8::StringUtf8(const char* String): StringUtf8((const u1*)String, (usz)strlen(String))
    {
    }

    StringUtf8::StringUtf8(const StringUtf8& Other) : StringUtf8(Other.Data, Other.NumBytes)
    {

    }

    StringUtf8::StringUtf8(StringUtf8&& Other) noexcept : Data(Other.Data), NumBytes(Other.NumBytes)
    {
        Other.Data = nullptr;
        Other.NumBytes = 0;
    }

    StringUtf8::~StringUtf8()
    {
        if (Data)
        {
            Memory::Free(Data);
        }
    }

    bool StringUtf8::EqualsBytes(const StringUtf8& Other) const
    {
        if (NumBytes == Other.NumBytes)
        {
            return Memory::Memcmp(Data, Other.Data, NumBytes) == 0;
        }
        else
        {
            return false;
        }
    }

    usz StringUtf8::GetNumBytes() const
    {
        return NumBytes;
    }

    StringUtf8::operator std::string() const
    {
        std::string AsString((char*)Data, NumBytes);
        return std::move(AsString);
    }

    StringUtf8& StringUtf8::operator=(StringUtf8&& Other) noexcept
    {
        Data = Other.Data;
        Other.Data = nullptr;

        NumBytes = Other.NumBytes;
        Other.NumBytes = 0;

        return *this;
    }
}