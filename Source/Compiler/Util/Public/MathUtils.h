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
                    CONSTEXPR_ASSERT(false, "Not implemented");
                }
            }
            else
            {
                CONSTEXPR_ASSERT(false, "Not implemented");
            }
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
    };
}
