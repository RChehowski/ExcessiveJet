
#pragma once

#include "Model/ClassReader.h"

#include <vector>

namespace Util
{
    template<typename TNumItems, typename TItem>
    class TSerializedArray;

    /**
     * The TSerializedArray with [TNumItems=u2]
     */
    template<typename TItem>
    using TStandardSerializedArray = TSerializedArray<u2, TItem>;


    template<typename TNumItems, typename TItem>
    class TSerializedArray : public std::vector<TItem>
    {
        static_assert(std::is_arithmetic_v<TNumItems>, "TNumItems must be arithmetic");
        static_assert(std::is_unsigned_v<TNumItems>, "TNumItems must be unsigned");

        static_assert(std::is_constructible<TItem>::value, "TItem must be default-constructible");

    public:
        using NumItemsType = TNumItems;

        friend void operator>>
        (
            Compiler::CClassReader &Reader,
            TStandardSerializedArray<std::shared_ptr<class CAttributeInfo>> &Instance
        );
    };


    template<typename TNumItems, typename TItem>
    Compiler::CClassReader& operator>>(Compiler::CClassReader &Reader, TSerializedArray<TNumItems, TItem> &SerializedArray)
    {
        static_assert(std::is_arithmetic_v<TNumItems>, "TNumItems$ must be arithmetic");

        TNumItems NumItems { static_cast<TNumItems>(0) };
        Reader >> NumItems;

        SerializedArray.clear();
        SerializedArray.reserve((usz) NumItems);

        for (usz Index = 0; Index < (usz) NumItems; ++Index)
        {
            TItem Item{};
            Reader >> Item;

            SerializedArray.push_back(std::move(Item));
        }

        return Reader;
    }
}
