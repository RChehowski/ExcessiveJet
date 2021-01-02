//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    class CByteOrder
    {
        friend class CMemoryFileEndian;

    public:
        constexpr explicit CByteOrder(const char* InName) : Name(InName)
        {
        }

        [[nodiscard]]
        constexpr bool IsNative() const;

    private:
        const char* Name;
    };

    class CByteOrders
    {
    private:
        static constexpr const CByteOrder BigEndianField = CByteOrder("Big Endian");
        static constexpr const CByteOrder LittleEndianField = CByteOrder("Little Endian");

        static constexpr bool IsNativeLittleEndian()
        {
            return true;
        }

    public:
        static constexpr const CByteOrder* BigEndian()
        {
            return &BigEndianField;
        }

        static constexpr const CByteOrder* LittleEndian()
        {
            return &LittleEndianField;
        }

        static constexpr const CByteOrder* NativeEndian()
        {
            return IsNativeLittleEndian() ? LittleEndian() : BigEndian();
        }
    };

    constexpr bool CByteOrder::IsNative() const
    {
        return this == CByteOrders::NativeEndian();
    }
}
