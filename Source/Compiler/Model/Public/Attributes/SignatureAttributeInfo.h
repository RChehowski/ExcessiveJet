//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "Attributes/AttributeInfo.h"

namespace Compiler
{
    class CClassReader;

    class CSignatureAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CSignatureAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(Signature);

        [[nodiscard]]
        FORCEINLINE u2 GetSignatureIndex() const
        {
            return SignatureIndex;
        }

    private:
        u2 SignatureIndex = (u2)0;
    };
}
