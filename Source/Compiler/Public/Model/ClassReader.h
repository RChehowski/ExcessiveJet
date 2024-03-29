//
// Created by ASUS on 29/12/2020.
//

#pragma once

#include <memory>

#include "Util/MemoryReader.h"
#include "Util/ByteOrder.h"

using Util::CByteOrders;

namespace Compiler
{
    class CConstantPool;

    class CClassReader : public Util::CMemoryReader
    {
        using Super = Util::CMemoryReader;

    public:
        FORCEINLINE explicit CClassReader(const std::string& InFileName)
            : Super(InFileName, /* Java classes are serialized using big endian byte order */ CByteOrders::GetBigEndian())
        {
        }

        FORCEINLINE explicit CClassReader(Util::CAllocation&& InAllocation)
            : Super(std::move(InAllocation), /* Java classes are serialized using big endian byte order */ CByteOrders::GetBigEndian())
        {
        }

        [[nodiscard]]
        FORCEINLINE std::shared_ptr<CConstantPool> GetConstantPool() const
        {
            ASSERT(ConstantPool != nullptr);
            return ConstantPool;
        }

        FORCEINLINE void SetConstantPool(const std::shared_ptr<CConstantPool>& InConstantPool)
        {
            ConstantPool = InConstantPool;
        }

        template<class T>
        FORCEINLINE friend void operator>> (CClassReader& Reader, std::shared_ptr<T> SharedPtrItem)
        {
            ASSERT(SharedPtrItem != nullptr);
            Reader >> *(SharedPtrItem.get());
        }

        friend void operator>>(CClassReader &Reader, class CClassInfo &Instance);

        [[nodiscard]]
        bool IsValid() const override
        {
            return bValid;
        }

    private:
        /**
         * To read attributes, the class reader must hold a reference to the deserialized ConstantPool.
         */
        std::shared_ptr<CConstantPool> ConstantPool;

        bool bValid = false;
    };
}
