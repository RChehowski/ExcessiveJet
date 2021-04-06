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

        template <typename T>
        FORCEINLINE static void ToggleEndian(T* ValuePtr)
        {
            const T Original = *ValuePtr;
            T Result = (T)0;

            for (u1 i = 0; i < (u1)sizeof(T); ++i)
            {
                const u1 ReadShift = (sizeof(T) - i - 1) * 8;
                const u1 WriteShift = i * 8;

                const T ReadMask = (T)0xFF;
                const T WriteMask = ((T)0xFF) << WriteShift;

                Result |= (T)((T)((T)(Original >> ReadShift) & ReadMask) << WriteShift) & WriteMask;
            }

            *ValuePtr = Result;
        }

        template<typename TTo, typename TFrom /* auto */>
        FORCEINLINE static TTo IntegerCast(TFrom From)
        {
            static_assert(std::is_integral_v<TTo> && std::is_integral_v<TTo>,
                    "IntegerCast is valid for integral types only");

//            if constexpr (sizeof(TTo) <= sizeof(TFrom))
//            {
//                if constexpr (std::is_signed_v<TFrom> != std::is_signed_v<TTo>)
//                {
//                    if constexpr (std::is_signed_v<TFrom>)
//                    {
//                        // From signed to unsigned. From should be greater or equal to zero.
//                        ASSERT(From >= (TFrom) 0);
//                    }
//                    else
//                    {
//                        // From unsigned to signed
//                        ASSERT(From <= );
//                    }
//                }
//                else if constexpr (sizeof(TTo) < sizeof(TFrom))
//                {
//                    // Both TTo and TFrom are either signed or unsigned
//                    ASSERT(
//                        (From >= (TFrom) std::numeric_limits<TTo>::min()) &&
//                        (From <= (TFrom) std::numeric_limits<TTo>::max())
//                    );
//                }
//            }

            return (TTo)From;
        }

        /**
         * Aligns a value to the nearest higher multiple of 'Alignment', which must be a power of two.
         *
         * @param  Val        The value to align.
         * @param  Alignment  The alignment value, must be a power of two.
         *
         * @return The value aligned up to the specified alignment.
         */
        template <typename T>
        FORCEINLINE static constexpr T Align(T Val, u8 Alignment)
        {
            static_assert(std::is_integral_v<T> || std::is_pointer_v<T>,
                    "Align expects an integer or pointer type");

            return (T)(((u8)Val + Alignment - 1) & ~(Alignment - 1));
        }

        /**
         * Aligns a value to the nearest lower multiple of 'Alignment', which must be a power of two.
         *
         * @param  Val        The value to align.
         * @param  Alignment  The alignment value, must be a power of two.
         *
         * @return The value aligned down to the specified alignment.
         */
        template <typename T>
        FORCEINLINE static constexpr T AlignDown(T Val, u8 Alignment)
        {
            static_assert(std::is_integral_v<T> || std::is_pointer_v<T>,
                          "AlignDown expects an integer or pointer type");

            return (T)(((u8)Val) & ~(Alignment - 1));
        }

        /**
         * Checks if a pointer is aligned to the specified alignment.
         *
         * @param  Val        The value to align.
         * @param  Alignment  The alignment value, must be a power of two.
         *
         * @return true if the pointer is aligned to the specified alignment, false otherwise.
         */
        template <typename T>
        FORCEINLINE static constexpr bool IsAligned(T Val, u8 Alignment)
        {
            static_assert(std::is_integral_v<T> || std::is_pointer_v<T>,
                          "IsAligned expects an integer or pointer type");

            return !((u8)Val & (Alignment - 1));
        }

        /**
         * Aligns a value to the nearest higher multiple of 'Alignment'.
         *
         * @param  Val        The value to align.
         * @param  Alignment  The alignment value, can be any arbitrary value.
         *
         * @return The value aligned up to the specified alignment.
         */
        template <typename T>
        FORCEINLINE static constexpr T AlignArbitrary(T Val, u8 Alignment)
        {
            static_assert(std::is_integral_v<T> || std::is_pointer_v<T>,
                    "AlignArbitrary expects an integer or pointer type");

            return (T)((((u8)Val + Alignment - 1) / Alignment) * Alignment);
        }


        FORCEINLINE static constexpr u8 Convert2U32ToU64(const u4 HighBytes, const u4 LowBytes)
        {
            return  (u8)(((u8)HighBytes << 32) & 0xFFFFFFFF00000000ULL) |
                    (u8)(((u8)LowBytes) & 0x00000000FFFFFFFFULL);
        }

        FORCEINLINE static constexpr u2 Convert2U1To1U2(const u1 HighByte, const u1 LowByte)
        {
            const u2 HighHalf   = (u2)((u2)HighByte << (u2)8) & (u2)0xFF00;
            const u2 LowHalf    = (u2)LowByte & (u2)0x00FF;

            return HighByte | LowByte;
        }

        template<class T>
        FORCEINLINE static constexpr usz ConvertToUsz(const T Value)
        {
            static_assert(std::is_integral_v<T>, "T must be integral");

            return static_cast<T>(Value);
        }
    };
}
