//
// Created by ASUS on 13/02/2021.
//

#pragma once

#include "Util/Types.h"
#include "ByteOrder.h"

namespace Util
{
    FORCEINLINE u1 CombineBytes(const CByteOrder* ByteOrder, u1 Byte0)
    {
        return Byte0;
    }

    FORCEINLINE u2 CombineBytes(const CByteOrder* ByteOrder, u1 Byte0, u1 Byte1)
    {
        if (ByteOrder == CByteOrders::GetBigEndian())
        {
            return (u2)(0xFFFF & (
                (u2)(Byte0 << 8) & 0xFF00 |
                (u2)(Byte1 << 0) & 0x00FF
            ));
        }
        else
        {
            return (u2)(0xFFFF & (
                (u2)(Byte1 << 8) & 0xFF00 |
                (u2)(Byte0 << 0) & 0x00FF
            ));
        }
    }

    FORCEINLINE u4 CombineBytes(const CByteOrder* ByteOrder, u1 Byte0, u1 Byte1, u1 Byte2, u1 Byte3)
    {
        if (ByteOrder == CByteOrders::GetBigEndian())
        {
            return (u4)(0xFFFFFFFF & (
                (u4)(Byte0 <<24) & 0xFF000000 |
                (u4)(Byte1 <<16) & 0x00FF0000 |
                (u4)(Byte2 << 8) & 0x0000FF00 |
                (u4)(Byte3 << 0) & 0x000000FF
            ));
        }
        else
        {
            return (u4)(0xFFFFFFFF & (
                (u4)(Byte3 <<24) & 0xFF000000 |
                (u4)(Byte2 <<16) & 0x00FF0000 |
                (u4)(Byte1 << 8) & 0x0000FF00 |
                (u4)(Byte0 << 0) & 0x000000FF
            ));
        }
    }

    template<typename TItem, typename... TArgs>
    constexpr void ExplodeBytes(const Util::CByteOrder* ByteOrder, const TItem& Item, TArgs*... OutBytes)
    {
        constexpr const usz SizeOfItem = (usz)sizeof(Item);
        constexpr const usz NumOutBytes = (usz)sizeof...(TArgs);

        static_assert(std::conjunction<std::is_same<u1, TArgs>...>::value, "All provided \"Args\" types must be u1 (bytes)");
        static_assert(SizeOfItem == NumOutBytes, "Invalid number of bytes provided, provide as many bytes as sizeof(Item)");

        const u1* const ItemBytes = reinterpret_cast<const u1*>(&Item);
        std::array<u1*, NumOutBytes> OutByteArray { OutBytes... };

        for (usz ItemByteIndex = (usz)0; ItemByteIndex < SizeOfItem; ++ItemByteIndex)
        {
            const usz OutByteIndex = Util::CByteOrders::IsNativeEndian(ByteOrder)
                                     ? ItemByteIndex
                                     : (SizeOfItem - ItemByteIndex) - 1
            ;

            *OutByteArray[OutByteIndex] = ItemBytes[ItemByteIndex];
        }
    }
}