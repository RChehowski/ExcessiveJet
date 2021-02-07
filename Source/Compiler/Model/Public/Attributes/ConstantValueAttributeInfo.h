//
// Created by ASUS on 05/01/2021.
//

#pragma once

#include "AttributeInfo.h"
#include "ClassReader.h"


class CClassReader;

namespace Parse
{
    class CConstantValueAttributeInfo final : public CAttributeInfo
    {
    public:
        [[nodiscard]]
        FORCEINLINE u2 GetConstantValueIndex() const
        {
            return ConstantValueIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(ConstantValue);

    private:
        u2 ConstantValueIndex = (u2)0;
    };
}
