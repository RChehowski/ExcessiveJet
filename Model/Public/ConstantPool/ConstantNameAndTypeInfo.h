#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantNameAndTypeInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetNameIndex() const
        {
             return NameIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
             return DescriptorIndex;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

        friend void operator>>(Util::CMemoryReader& Reader, CConstantNameAndTypeInfo& Instance);

    private:
        u2 NameIndex = (u2)0;
        u2 DescriptorIndex = (u2)0;
    };
}