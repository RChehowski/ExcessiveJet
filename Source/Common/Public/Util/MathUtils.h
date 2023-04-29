//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Util/Types.h"
#include "Util/Platform/Memory.h"

namespace Util
{
    namespace Private
    {
        template <typename T>
        void ToggleEndian(T* ValuePtr);

#ifdef EXJ_ENDIAN_BYTE_SWAP
    #error EXJ_ENDIAN_BYTE_SWAP
#endif
#define EXJ_ENDIAN_BYTE_SWAP(a, b) { u1 _temp = (a); (a) = (b); (b) = _temp; }

        template <>
        FORCEINLINE void ToggleEndian<u1>(u1* const ValuePtr)
        {
            // Nothing to do with the 1 byte value
        }

        template <>
        FORCEINLINE void ToggleEndian<u2>(u2* const ValuePtr)
        {
            struct CBytes
            {
                u1 Byte0;
                u1 Byte1;
            };
            CBytes* const Bytes = reinterpret_cast<CBytes*>(ValuePtr);

            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte0, Bytes->Byte1)
        }

        template <>
        FORCEINLINE void ToggleEndian<u4>(u4* const ValuePtr)
        {
            struct CBytes
            {
                u1 Byte0;
                u1 Byte1;
                u1 Byte2;
                u1 Byte3;
            };
            CBytes* const Bytes = reinterpret_cast<CBytes*>(ValuePtr);

            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte0, Bytes->Byte3)
            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte1, Bytes->Byte2)
        }

        template <>
        FORCEINLINE void ToggleEndian<u8>(u8* const ValuePtr)
        {
            struct CBytes
            {
                u1 Byte0;
                u1 Byte1;
                u1 Byte2;
                u1 Byte3;
                u1 Byte4;
                u1 Byte5;
                u1 Byte6;
                u1 Byte7;
            };
            CBytes* const Bytes = reinterpret_cast<CBytes*>(ValuePtr);

            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte0, Bytes->Byte7)
            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte1, Bytes->Byte6)
            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte2, Bytes->Byte5)
            EXJ_ENDIAN_BYTE_SWAP(Bytes->Byte3, Bytes->Byte4)
        }

#undef EXJ_BYTE_SWAP
    }

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

        /** Toggles the endian (little -> big or big -> little) of a value pointed by the pointer */
        template <typename T>
        FORCEINLINE static void ToggleEndian(T* ValuePtr)
        {
            Private::ToggleEndian(ValuePtr);
        }

        template<typename TTo, typename TFrom /* auto */>
        FORCEINLINE static TTo IntegerCast(TFrom From)
        {
            static_assert(std::is_integral_v<TTo> && std::is_integral_v<TTo>,
                    "IntegerCast is valid for integral types only");

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
        template <typename TValue>
        FORCEINLINE static constexpr bool IsAligned(TValue Val, u8 Alignment)
        {
            static_assert(std::is_integral_v<TValue> || std::is_pointer_v<TValue>,
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

        template <typename TEnum>
        FORCEINLINE static constexpr bool EnumHasFlag(TEnum Test, TEnum Flags)
        {
            return (Test & Flags) != 0;
        }

        template<typename TRange, typename TNumber>
        FORCEINLINE static constexpr bool IsNumberWithinRange
        (
            const TNumber Number,
            const TRange RangeMin = std::numeric_limits<TRange>::min(),
            const TRange RangeMax = std::numeric_limits<TRange>::max()
        )
        {
            static_assert(std::numeric_limits<TNumber>::min() <= std::numeric_limits<TRange>::min());
            static_assert(std::numeric_limits<TNumber>::max() >= std::numeric_limits<TRange>::max());

            return (Number >= static_cast<TNumber>(RangeMin)) && (Number <= static_cast<TNumber>(RangeMax));
        }
    };
}
