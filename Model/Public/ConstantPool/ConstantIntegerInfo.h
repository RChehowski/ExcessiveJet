#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantIntegerInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u4 GetBytes() const
        {
             return Bytes;
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantIntegerInfo& Instance);

    private:
        u4 Bytes = (u4)0;
    };
}