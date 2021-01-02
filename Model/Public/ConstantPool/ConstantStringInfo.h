#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantStringInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetStringIndex() const
        {
             return StringIndex;
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantStringInfo& Instance);

    private:
        u2 StringIndex = (u2)0;
    };
}