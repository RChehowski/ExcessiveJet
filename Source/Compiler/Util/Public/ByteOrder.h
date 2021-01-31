//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    class CByteOrder
    {
        friend class CByteOrders;

    private:
        /**
         * The constructor is private since these instances should be constexpr-constructible
         * only from the 'enclosing' class (CByteOrders)
         *
         * @param InName The name of the ByteOrder.
         */
        constexpr explicit CByteOrder(const char* InName) : Name(InName) {}

    public:
        [[nodiscard]]
        constexpr bool IsNative() const;

        [[nodiscard]]
        constexpr const char* GetName() const
        {
            return Name;
        }

    private:
        const char* Name;
    };


    class CByteOrders
    {
    public:
        static constexpr const CByteOrder* GetBigEndian()
        {
            return &BigEndian;
        }

        static constexpr const CByteOrder* GetLittleEndian()
        {
            return &LittleEndian;
        }

        static constexpr const CByteOrder* GetNativeEndian()
        {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
            return GetLittleEndian();
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
            return GetBigEndian();
#else
            #error "Unknown endian!"
#endif
        }

    private:
        static constexpr const CByteOrder BigEndian = CByteOrder("Big Endian");
        static constexpr const CByteOrder LittleEndian = CByteOrder("Little Endian");
    };

    constexpr bool CByteOrder::IsNative() const
    {
        return this == CByteOrders::GetNativeEndian();
    }
}
