//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Types.h"
#include "Platform/Memory.h"

namespace Util
{
    class CMathUtils
    {
    public:
        template<typename T>
        FORCEINLINE static T Max(T A, T B)
        {
            return (A > B) ? A : B;
        }

        template<typename T>
        FORCEINLINE static T Min(T A, T B)
        {
            return (A > B) ? A : B;
        }

        template<typename T>
        FORCEINLINE static T Clamp(T InValue, T InMin, T InMax)
        {
            return Max<T>(Min<T>(InValue, InMax), InMin);
        }

        FORCEINLINE static void TwiddleBytes(u1* Bytes, const usz Size)
        {
            switch (Size)
            {
                case 8: {
                    const u8 Value = *(u8 *) Bytes;
                    u8 Result = (u8) 0;

                    Result |= (((Value >> 0x38) & 0xFF) << 0x00) & 0x00000000000000FFULL;
                    Result |= (((Value >> 0x30) & 0xFF) << 0x08) & 0x000000000000FF00ULL;
                    Result |= (((Value >> 0x28) & 0xFF) << 0x10) & 0x0000000000FF0000ULL;
                    Result |= (((Value >> 0x20) & 0xFF) << 0x18) & 0x00000000FF000000ULL;

                    Result |= (((Value >> 0x18) & 0xFF) << 0x20) & 0x000000FF00000000ULL;
                    Result |= (((Value >> 0x10) & 0xFF) << 0x28) & 0x0000FF0000000000ULL;
                    Result |= (((Value >> 0x08) & 0xFF) << 0x30) & 0x00FF000000000000ULL;
                    Result |= (((Value >> 0x00) & 0xFF) << 0x38) & 0xFF00000000000000ULL;

                    Memory::Memcpy(Bytes, &Result, Size);
                    break;
                }
                case 4: {
                    const u4 Value = *(u4 *) Bytes;
                    u4 Result = (u4) 0;

                    Result |= (((Value >> 0x18) & 0xFF) << 0x00) & 0x000000FF;
                    Result |= (((Value >> 0x10) & 0xFF) << 0x08) & 0x0000FF00;
                    Result |= (((Value >> 0x08) & 0xFF) << 0x10) & 0x00FF0000;
                    Result |= (((Value >> 0x00) & 0xFF) << 0x18) & 0xFF000000;

                    Memory::Memcpy(Bytes, &Result, Size);
                    break;
                }
                case 2: {
                    const u2 Value = *(u2 *) Bytes;
                    u2 Result = (u2) 0;

                    Result |= (((Value >> 0x08) & 0xFF) << 0x00) & 0x00FF;
                    Result |= (((Value >> 0x00) & 0xFF) << 0x08) & 0xFF00;

                    Memory::Memcpy(Bytes, &Result, Size);
                    break;
                }
                case 1: {
                    break;
                }
                default:
                    // Assert
                    break;
            }
        }

        template<typename TTo, typename TFrom /* auto */>
        FORCEINLINE static TTo IntegerCast(TFrom From)
        {
            if constexpr (!std::is_signed_v<TFrom>)
            {
                if constexpr (!std::is_signed_v<TTo>)
                {
                    if constexpr (sizeof(TTo) >= sizeof(TFrom))
                    {
                        // Will not overflow
                        return static_cast<TTo>(From);
                    }
                    else
                    {
                        ASSERT(From <= (TFrom)std::numeric_limits<TTo>::max());
                        return static_cast<TTo>(From);
                    }
                }
                else
                {
                    []<bool flag = false>() { static_assert(flag, "Not implemented"); }();
                }
            }
            else
            {
                []<bool flag = false>() { static_assert(flag, "Not implemented"); }();
            }
        };
    };
}
