#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantFieldRefInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u2 GetClassIndex() const
        {
             return ClassIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameAndTypeIndex() const
        {
             return NameAndTypeIndex;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

        friend void operator>>(Util::CMemoryReader& Reader, CConstantFieldRefInfo& Instance);

    private:
        u2 ClassIndex = (u2)0;
        u2 NameAndTypeIndex = (u2)0;
    };
}