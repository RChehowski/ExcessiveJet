#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantMethodTypeInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
             return DescriptorIndex;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

        friend void operator>>(Util::CMemoryReader& Reader, CConstantMethodTypeInfo& Instance);

    private:
        u2 DescriptorIndex = (u2)0;
    };
}