
#pragma once

#include "MemoryFile.h"

#include <vector>

namespace Util
{
    template <typename TNumItems, typename TItem>
    class TSerializedArray
    {
        using VectorOfItems = std::vector<TItem>;
        using TIterator = typename VectorOfItems::iterator;
        using TConstIterator = typename VectorOfItems::const_iterator;

        static_assert(std::is_arithmetic_v<TNumItems>, "TNumItems must be arithmetic");
        static_assert(std::is_trivially_constructible_v<TItem>, "TNumItems must be trivially constructible");
        static_assert(std::is_trivially_move_assignable_v<TItem>, "TNumItems must be trivially constructible");

        template <typename TNumItemsFunc, typename TItemFunc>
        friend void operator>> (Util::CMemoryReader& Reader, TSerializedArray<TNumItemsFunc, TItemFunc>& SerializedArray);

    public:
        TSerializedArray() = default;
        ~TSerializedArray() = default;


        FORCEINLINE TIterator begin() noexcept
        {
            return Items.begin();
        }

        FORCEINLINE TIterator end() noexcept
        {
            return Items.end();
        }


        FORCEINLINE TConstIterator cbegin() const noexcept
        {
            return Items.cbegin();
        }

        FORCEINLINE TConstIterator cend() const noexcept
        {
            return Items.cend();
        }


        [[nodiscard]]
        FORCEINLINE usz Size() const noexcept
        {
            return (usz)Items.size();
        }

        [[nodiscard]]
        FORCEINLINE TItem& operator[](usz Index) noexcept
        {
            return Items[Index];
        }

        [[nodiscard]]
        FORCEINLINE const TItem& operator[](usz Index) const noexcept
        {
            return Items[Index];
        }

    private:
        VectorOfItems Items;
    };


    template <typename TNumItemsFunc, typename TItemFunc>
    void operator>> (Util::CMemoryReader& Reader, TSerializedArray<TNumItemsFunc, TItemFunc>& SerializedArray)
    {
        TNumItemsFunc NumItems = (TNumItemsFunc)0;
        Reader >> NumItems;

        SerializedArray.Items.clear();
        SerializedArray.Items.reserve((usz)NumItems);

        for (usz Index = 0; Index < (usz)NumItems; ++Index)
        {
            TItemFunc Item;
            Reader >> Item;

            SerializedArray.Items.push_back(std::move(Item));
        }
    }
}