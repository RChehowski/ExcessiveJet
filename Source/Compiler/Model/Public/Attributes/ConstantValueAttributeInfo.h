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
        using CAttributeInfo::CAttributeInfo;

        [[nodiscard]]
        FORCEINLINE u2 GetConstantValueIndex() const
        {
            return ConstantValueIndex;
        }

        void DeserializeBody(CClassReader& Reader) override;

    private:
        u2 ConstantValueIndex = (u2)0;
    };
}