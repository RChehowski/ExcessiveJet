#pragma once

#include "ConstantPool/ConstantInfo.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantMethodHandleInfo : public CConstantInfo
    {
    public:
        using CConstantInfo::CConstantInfo;

        std::string ToString() const override;

        [[nodiscard]]
        FORCEINLINE u1 GetReferenceKind() const
        {
             return ReferenceKind;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetReferenceIndex() const
        {
             return ReferenceIndex;
        }

        friend void operator>>(Util::CMemoryReader& Reader, CConstantMethodHandleInfo& Instance);

    private:
        u1 ReferenceKind = (u1)0;
        u2 ReferenceIndex = (u2)0;
    };
}