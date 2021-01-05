//
// Created by ASUS on 30/12/2020.
//

#include "StringUtf8.h"

namespace Util
{
    u1* CopyBytes(const u1* InBytes, usz InNumBytes)
    {
        u1* const Bytes = Memory::MallocT<u1>(InNumBytes);
        Memory::Memcpy(Bytes, InBytes, InNumBytes);
        return Bytes;
    }

    CStringUtf8::CStringUtf8() : IStringUtf8(nullptr, (usz)0)
    {

    }

    CStringUtf8::CStringUtf8(const char* String): CStringUtf8((const u1*)String, (usz)strlen(String))
    {
    }

    CStringUtf8::CStringUtf8(const u1* InBytes, usz InNumBytes)
        : IStringUtf8(CopyBytes(InBytes, InNumBytes), InNumBytes)
    {

    }

    CStringUtf8::CStringUtf8(const CStringUtf8& Other) : CStringUtf8(Other.Bytes, Other.NumBytes)
    {

    }

    CStringUtf8::CStringUtf8(CStringUtf8&& Other) noexcept : IStringUtf8(Other.Bytes, Other.NumBytes)
    {
        Other.Bytes = nullptr;
        Other.NumBytes = 0;
    }

    CStringUtf8::~CStringUtf8()
    {
        if (Bytes)
        {
            Memory::Free(Bytes);
        }
    }

    CStringUtf8::operator std::string() const
    {
        std::string AsString((char*)Bytes, NumBytes);
        return std::move(AsString);
    }

    CStringUtf8& CStringUtf8::operator=(CStringUtf8&& Other) noexcept
    {
        Bytes = Other.Bytes;
        Other.Bytes = nullptr;

        NumBytes = Other.NumBytes;
        Other.NumBytes = 0;

        return *this;
    }
}