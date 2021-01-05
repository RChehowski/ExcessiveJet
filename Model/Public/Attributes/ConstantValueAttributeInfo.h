//
// Created by ASUS on 05/01/2021.
//

#pragma once

#include "AttributeInfo.h"


namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantValueAttributeInfo final : public CAttributeInfo
    {
    public:
        using CAttributeInfo::CAttributeInfo;

        [[nodiscard]]
        FORCEINLINE u2 GetConstantValueIndex() const
        {
            return ConstantValueIndex;
        }

        void DeserializeFrom(Util::CMemoryReader& Reader) override;

    private:
        u2 ConstantValueIndex = (u2)0;
    };
}
