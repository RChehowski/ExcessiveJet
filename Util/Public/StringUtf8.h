//
// Created by ASUS on 30/12/2020.
//

#ifndef CPP20_STRINGUTF8_H
#define CPP20_STRINGUTF8_H

#include "Types.h"
#include "Platform/Memory.h"

#include <string>


namespace Util
{
    class StringUtf8 final
    {
    public:
        StringUtf8();
        StringUtf8(const u1* InData, usz InNumBytes);
        StringUtf8(const char* String);
        StringUtf8(const StringUtf8& Other);
        StringUtf8(StringUtf8&& Other) noexcept;

        ~StringUtf8();

        [[nodiscard]]
        bool EqualsBytes(const StringUtf8& Other) const;

        [[nodiscard]]
        usz GetNumBytes() const;

        FORCEINLINE u1 GetByte(const usz Index) const
        {
            return Data[Index];
        }

        FORCEINLINE bool operator==(const StringUtf8& Other) const
        {
            return EqualsBytes(Other);
        }

        explicit operator std::string() const;

        StringUtf8& operator=(StringUtf8&& Other) noexcept;



    private:
        u1* Data;
        usz NumBytes;
    };
}

namespace std
{
    template<>
    struct hash<Util::StringUtf8>
    {
        std::size_t operator()(const Util::StringUtf8 &InStringUtf8) const
        {
            size_t Result = 0;
            const size_t Prime = 31;

            for (size_t Index = 0; Index < InStringUtf8.GetNumBytes(); ++Index)
            {
                Result = InStringUtf8.GetByte(Index) + (Result * Prime);
            }

            return Result;
        }
    };
}


#endif //CPP20_STRINGUTF8_H
