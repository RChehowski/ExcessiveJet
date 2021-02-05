//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "Attributes/AttributeInfo.h"

namespace Parse
{
    class CClassReader;

    class CSignatureAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CSignatureAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

    private:
        u2 SignatureIndex = (u2)0;
    };
}
