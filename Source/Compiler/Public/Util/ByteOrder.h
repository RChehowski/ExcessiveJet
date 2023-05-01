//
// Created by ASUS on 02/01/2021.
//

#pragma once

#include "Util/Types.h"

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
        // non-copyable
        CByteOrder(const CByteOrder&) = delete;
        CByteOrder(CByteOrder&&) = delete;

        // non-assignable
        CByteOrder& operator=(const CByteOrder&) = delete;
        CByteOrder& operator=(CByteOrder&&) = delete;

        [[nodiscard]]
        bool IsNative() const;

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
        static constexpr const CByteOrder& GetBigEndian()
        {
            return BigEndian;
        }

        static constexpr const CByteOrder& GetLittleEndian()
        {
            return LittleEndian;
        }

        static const CByteOrder& GetNativeEndian()
        {
            return IsNativeLittleEndian() ? GetLittleEndian() : GetBigEndian();
        }

    private:
        static constexpr const CByteOrder BigEndian { "Big Endian" };
        static constexpr const CByteOrder LittleEndian { "Little Endian" };
    };

    FORCEINLINE bool CByteOrder::IsNative() const
    {
        return this == &CByteOrders::GetNativeEndian();
    }
}
