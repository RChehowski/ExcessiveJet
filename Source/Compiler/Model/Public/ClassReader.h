//
// Created by ASUS on 29/12/2020.
//

#pragma once

#include "MemoryReader.h"

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

    private:
        std::shared_ptr<CConstantPool> ConstantPool;
    };
}
