#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantInvokeDynamicInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetBootstrapMethodAttrIndex() const
        {
             return BootstrapMethodAttrIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameAndTypeIndex() const
        {
             return NameAndTypeIndex;
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantInvokeDynamicInfo& Instance);

    private:
        u2 BootstrapMethodAttrIndex = (u2)0;
        u2 NameAndTypeIndex = (u2)0;
    };
}