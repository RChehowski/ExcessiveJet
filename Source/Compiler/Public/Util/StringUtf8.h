//
// Created by ASUS on 30/12/2020.
//

#ifndef CPP20_STRINGUTF8_H
#define CPP20_STRINGUTF8_H

#include "Util/Types.h"
#include "Platform/Memory.h"


#include <string>
#include <cstring>
#include <ostream>


namespace Util
{
    u1* CopyBytes(const u1* InBytes, usz InNumBytes);

    class IStringUtf8
    {
    protected:
        constexpr IStringUtf8(const u1* InBytes, usz InNumBytes, bool bInOwnsItsBytes)
            : Bytes(InBytes)
            , NumBytes(InNumBytes)
            , bOwnsItsBytes(bInOwnsItsBytes)
        {
        }

    public:
        IStringUtf8(const IStringUtf8& Other)
            : Bytes(Other.bOwnsItsBytes ? CopyBytes(Other.Bytes, Other.NumBytes) : Other.Bytes)
            , NumBytes(Other.NumBytes)
            , bOwnsItsBytes(Other.bOwnsItsBytes)
        {
        }

        ~IStringUtf8()
        {
            if (Bytes && bOwnsItsBytes)
            {
                CMemory::Free(Bytes);
            }
        }

        [[nodiscard]]
        constexpr u1 GetByteAt(usz Index) const
        {
            return Bytes[Index];
        }

        [[nodiscard]]
        constexpr usz GetNumBytes() const
        {
            return NumBytes;
        }

        [[nodiscard]]
        constexpr const u1* GetBytes() const
        {
            return Bytes;
        }

        [[nodiscard]]
        constexpr bool EqualsBytes(const IStringUtf8& Other) const
        {
            if (NumBytes == Other.NumBytes)
            {
                for (usz Index = 0; Index < NumBytes; ++Index)
                {
                    if (GetByteAt(Index) != Other.GetByteAt(Index))
                    {
                        return false;
                    }
                }

                return true;
            }
            else
            {
                return false;
            }
        }

        [[nodiscard]]
        bool EqualsBytes(const char* Other) const
        {
            return EqualsBytes(IStringUtf8((u1*)Other, (usz)std::char_traits<char>::length(Other), false));
        }

        constexpr bool operator==(const IStringUtf8& Other) const
        {
            return EqualsBytes(Other);
        }

        friend std::ostream& operator<< (std::ostream& ostream, const IStringUtf8& Instance)
        {
            ostream.write(reinterpret_cast<const char*>(Instance.Bytes), (std::streamsize)Instance.NumBytes);
            return ostream;
        }

        explicit operator std::string() const
        {
            return std::string {(char*)Bytes, NumBytes };
        }

        IStringUtf8& operator=(IStringUtf8&& Other) noexcept
        {
            if (bOwnsItsBytes)
                CMemory::Free((void*)Bytes);

            Bytes = Other.Bytes;

            if (Other.bOwnsItsBytes)
                Other.Bytes = nullptr;

            NumBytes = Other.NumBytes;

            if (Other.bOwnsItsBytes)
                Other.NumBytes = 0;

            return *this;
        }

    protected:
        const u1* Bytes;
        usz NumBytes;

    private:
        const bool bOwnsItsBytes;
    };

    class CStringUtf8 final : public IStringUtf8
    {
    public:
        CStringUtf8();
        explicit CStringUtf8(const char* String);
        CStringUtf8(const u1* InBytes, usz InNumBytes);
        CStringUtf8(const CStringUtf8& Other);
        CStringUtf8(CStringUtf8&& Other) noexcept;

        CStringUtf8& operator=(CStringUtf8&& Other) noexcept;
    };

    class CLiteralStringUtf8 final : public IStringUtf8
    {
    public:
        explicit CLiteralStringUtf8(const char* String)
            : IStringUtf8(
                (const u1*)String,
                std::char_traits<char>::length(String),
                false
            )
        {
        }
    };
}

namespace std
{
    template<>
    struct hash<Util::IStringUtf8>
    {
        constexpr std::size_t operator()(const Util::IStringUtf8 &InStringUtf8) const
        {
            std::size_t Result = 0;
            const std::size_t Prime = 31;

            for (usz Index = 0; Index < InStringUtf8.GetNumBytes(); ++Index)
            {
                Result = InStringUtf8.GetByteAt(Index) + (Result * Prime);
            }

            return Result;
        }
    };
}


#endif //CPP20_STRINGUTF8_H
