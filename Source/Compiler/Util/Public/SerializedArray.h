
#pragma once

//#include "ClassReader.h"

#include <vector>

namespace Parse
{
    class CClassReader;
}

namespace Util
{
    template<typename TNumItems, typename TItem>
    class TSerializedArray;

    /**
     * The TSerializedArray with [TNumItems=u2]
     */
    template<typename TItem>
    using TStandardSerializedArray = TSerializedArray<u2, TItem>;

    using CSerializedArrayOfAttributes = Util::TStandardSerializedArray<class CSharedAttributeInfo>;

    template<typename TNumItems, typename TItem>
    class TSerializedArray
    {
        using VectorOfItems = std::vector<TItem>;

        using TIterator = typename VectorOfItems::iterator;
        using TConstIterator = typename VectorOfItems::const_iterator;

        static_assert(std::is_arithmetic_v<TNumItems>, "TNumItems must be arithmetic");
        static_assert(std::is_unsigned_v<TNumItems>, "TNumItems must be unsigned");

//        static_assert(std::is_trivially_constructible_v<TItem>, "TItem must be trivially constructible");
//        static_assert(std::is_trivially_move_assignable_v<TItem>, "TItem must be trivially constructible");

//        template<typename TNumItemsFunc, typename TItemFunc>
//        friend void
//        operator>>(Parse::CClassReader &Reader, TSerializedArray<TNumItemsFunc, TItemFunc> &SerializedArray);

        friend void operator>>(
                Parse::CClassReader &Reader,
                TStandardSerializedArray<std::shared_ptr<class CAttributeInfo>> &Instance
        );

    public:
        using NumItemsType = TNumItems;
        using ItemType = TItem;

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


        FORCEINLINE TConstIterator begin() const noexcept
        {
            return Items.cbegin();
        }

        FORCEINLINE TConstIterator end() const noexcept
        {
            return Items.cend();
        }


        [[nodiscard]]
        FORCEINLINE usz Size() const noexcept
        {
            return (usz) Items.size();
        }

        [[nodiscard]]
        FORCEINLINE bool IsEmpty() const noexcept
        {
            return Size() == (usz)0;
        }

        FORCEINLINE void Clear(ssz NewSize = -1) noexcept
        {
            Items.clear();

            if (NewSize > 0)
            {
                Items.reserve(NewSize);
            }
        }

        [[nodiscard]]
        FORCEINLINE TItem &operator[](usz Index) noexcept
        {
            return Items[Index];
        }

        [[nodiscard]]
        FORCEINLINE const TItem &operator[](usz Index) const noexcept
        {
            return Items[Index];
        }

//    private:
        VectorOfItems Items;
    };


    template<typename TNumItems$, typename TItem$>
    Parse::CClassReader& operator>>(Parse::CClassReader &Reader, TSerializedArray<TNumItems$, TItem$> &SerializedArray)
    {
        static_assert(std::is_arithmetic_v<TNumItems$>, "TNumItems$ must be arithmetic");

        TNumItems$ NumItems = (TNumItems$) 0;
        Reader >> NumItems;

        SerializedArray.Items.clear();
        SerializedArray.Items.reserve((usz) NumItems);

        for (usz Index = 0; Index < (usz) NumItems; ++Index)
        {
            TItem$ Item;
            Reader >> Item;

            SerializedArray.Items.push_back(std::move(Item));
        }

        return Reader;
    }
}

namespace Parse
{
//    template <typename TNumItems$, typename TItem$>
//    CClassReader& operator>> (
//        //Parse::CClassReader& Reader, Util::TSerializedArray<TNumItems$, std::shared_ptr<TItem$>>& SerializedArray
//        CClassReader &,class Util::TSerializedArray<unsigned short,class std::shared_ptr<TItem$> > &
//    )
//    {
//        static_assert(std::is_arithmetic_v<TNumItems$>, "TNumItems$ must be arithmetic");
//
//        TNumItems$ NumItems = (TNumItems$)0;
//        Reader >> NumItems;
//
//        SerializedArray.Items.clear();
//        SerializedArray.Items.reserve((usz)NumItems);

//        for (usz Index = 0; Index < (usz)NumItems; ++Index)
//        {
//            TItem$ Item;
//            Reader >> Item;
//
//            SerializedArray.Items.push_back(std::move(Item));
//        }

//        return Reader;
//    }
}
