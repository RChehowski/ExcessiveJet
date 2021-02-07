//
// Created by ASUS on 05/01/2021.
//

#pragma once

#include "AttributeInfo.h"
#include "ClassReader.h"


class CClassReader;

namespace Parse
{
    class CEnclosingMethodAttributeInfo final : public CAttributeInfo
    {
    public:
        [[nodiscard]]
        FORCEINLINE u2 GetClassIndex() const
        {
            return ClassIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetMethodIndex() const
        {
            return MethodIndex;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(EnclosingMethod);

    private:
        u2 ClassIndex      = (u2)0;
        u2 MethodIndex     = (u2)0;
    };
}
