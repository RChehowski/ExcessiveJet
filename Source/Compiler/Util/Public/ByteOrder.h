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
    private:
        static constexpr const CByteOrder BigEndianField = CByteOrder("Big Endian");
        static constexpr const CByteOrder LittleEndianField = CByteOrder("Little Endian");

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
//            // TODO: Should be replaced with something simpler once it's available
//#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN || \
//    defined(__BIG_ENDIAN__) || \
//    defined(__ARMEB__) || \
//    defined(__THUMBEB__) || \
//    defined(__AARCH64EB__) || \
//    defined(_MIBSEB) || defined(__MIBSEB) || defined(__MIBSEB__)
//            // It's a big-endian target architecture
//            return BigEndian();
//#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN || \
//    defined(__LITTLE_ENDIAN__) || \
//    defined(__ARMEL__) || \
//    defined(__THUMBEL__) || \
//    defined(__AARCH64EL__) || \
//    defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
//            // It's a little-endian target architecture
//            return LittleEndian();
//#else
//#error "Unknown endian!"
//#endif
            return LittleEndian();
        }
    };

    constexpr bool CByteOrder::IsNative() const
    {
        return this == CByteOrders::NativeEndian();
    }
}
