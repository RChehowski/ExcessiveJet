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
        explicit CClassReader(const Util::WideString& InFileName) : Super (InFileName)
        {
        }

        [[nodiscard]]
        CConstantPool* GetConstantPool() const;

        void SetConstantPool(CConstantPool* InConstantPool);

    private:
        CConstantPool* ConstantPool = nullptr;
    };
}
