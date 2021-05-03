//
// Created by ASUS on 30/12/2020.
//

#include "StringUtf8.h"

#define DEBUG_NULL_TERMINATE_STRING (1)

namespace Util
{
    u1* CopyBytes(const u1* InBytes, usz InNumBytes)
    {
#if DEBUG_NULL_TERMINATE_STRING
        u1* const Bytes = CMemory::Malloc<u1>(InNumBytes + 1);
        CMemory::Memcpy(Bytes, InBytes, InNumBytes);
        Bytes[(usz)InNumBytes] = (u1)'\0';
#else
        u1* const Bytes = CMemory::MallocT<u1>(InNumBytes);
        CMemory::Memcpy(Bytes, InBytes, InNumBytes);
#endif // DEBUG_NULL_TERMINATE_STRING

        return Bytes;
    }

    CStringUtf8::CStringUtf8() : IStringUtf8(nullptr, (usz)0, false)
    {
    }

    CStringUtf8::CStringUtf8(const char* String) : CStringUtf8((const u1*)String, (usz)strlen(String))
    {
    }

    CStringUtf8::CStringUtf8(const u1* InBytes, usz InNumBytes) : IStringUtf8(CopyBytes(InBytes, InNumBytes), InNumBytes, true)
    {
    }

    CStringUtf8::CStringUtf8(const CStringUtf8& Other) : CStringUtf8(Other.Bytes, Other.NumBytes)
    {
    }

    CStringUtf8::CStringUtf8(CStringUtf8&& Other) noexcept : IStringUtf8(Other.Bytes, Other.NumBytes, true)
    {
        Other.Bytes = nullptr;
        Other.NumBytes = 0;
    }

    CStringUtf8& CStringUtf8::operator=(CStringUtf8&& Other) noexcept
    {
        CMemory::Free((void*)Bytes);
        Bytes = Other.Bytes;
        Other.Bytes = nullptr;

        NumBytes = Other.NumBytes;
        Other.NumBytes = 0;

        return *this;
    }
}