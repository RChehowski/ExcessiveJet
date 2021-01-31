//
// Created by ASUS on 29/12/2020.
//

#pragma once

#include "MemoryReader.h"
#include <memory>

namespace Parse
{
    class CConstantPool;

    class CClassReader : public Util::CMemoryReader
    {
        using Super = Util::CMemoryReader;

    public:
        explicit CClassReader(const Util::WideString& InFileName);

        [[nodiscard]]
        std::shared_ptr<CConstantPool> GetConstantPool() const;

        void SetConstantPool(const std::shared_ptr<CConstantPool>& InConstantPool);

        template<class T>
        friend void operator>> (CClassReader& Reader, std::shared_ptr<T> SharedPtrItem)
        {
            ASSERT(SharedPtrItem != nullptr);
            Reader >> *(SharedPtrItem.get());
        }

    private:
        std::shared_ptr<CConstantPool> ConstantPool;
    };
}
