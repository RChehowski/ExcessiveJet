//
// Created by ASUS on 29/12/2020.
//

#pragma once

#include <memory>

#include "MemoryReader.h"
#include "ByteOrder.h"

using Util::CByteOrders;

namespace Compiler
{
    class CConstantPool;

    class CClassReader : public Util::CMemoryReader
    {
        using Super = Util::CMemoryReader;

    public:
        FORCEINLINE explicit CClassReader(const std::string& InFileName) : Super(InFileName)
        {
            // Java classes are serialized using big endian byte order
            SetByteOrder(CByteOrders::GetBigEndian());
        }

        [[nodiscard]]
        FORCEINLINE std::shared_ptr<CConstantPool> GetConstantPool() const
        {
            ASSERT(ConstantPool != nullptr);
            return ConstantPool;
        }

        FORCEINLINE void SetConstantPool(const std::shared_ptr<CConstantPool>& InConstantPool)
        {
            ASSERT(ConstantPool == nullptr);
            ConstantPool = InConstantPool;
        }

        template<class T>
        FORCEINLINE friend void operator>> (CClassReader& Reader, std::shared_ptr<T> SharedPtrItem)
        {
            ASSERT(SharedPtrItem != nullptr);
            Reader >> *(SharedPtrItem.get());
        }

    private:
        /**
         * To read attributes, the class reader must hold a reference to the deserialized ConstantPool.
         */
        std::shared_ptr<CConstantPool> ConstantPool;
    };
}
