//
// Created by ASUS on 13/02/2021.
//

#pragma once

#include "Util/Types.h"
#include "ByteOrder.h"

namespace Util
{
    template<typename TItem, typename... TArgs>
    constexpr void ExplodeBytes(const Util::CByteOrder& ByteOrder, const TItem& Item, TArgs*... OutBytes)
    {
        constexpr const usz SizeOfItem = (usz)sizeof(Item);
        constexpr const usz NumOutBytes = (usz)sizeof...(TArgs);

        static_assert(std::conjunction<std::is_same<u1, TArgs>...>::value, "All provided \"Args\" types must be u1 (bytes)");
        static_assert(SizeOfItem == NumOutBytes, "Invalid number of bytes provided, provide as many bytes as sizeof(Item)");

        const u1* const ItemBytes = reinterpret_cast<const u1*>(&Item);
        std::array<u1*, NumOutBytes> OutByteArray { OutBytes... };

        for (usz ItemByteIndex = (usz)0; ItemByteIndex < SizeOfItem; ++ItemByteIndex)
        {
            const usz OutByteIndex = ByteOrder.IsNative()
                    ? ItemByteIndex
                    : (SizeOfItem - ItemByteIndex) - 1;

            *OutByteArray[OutByteIndex] = ItemBytes[ItemByteIndex];
        }
    }
}