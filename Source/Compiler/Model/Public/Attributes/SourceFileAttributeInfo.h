//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "Attributes/AttributeInfo.h"

namespace Parse
{
    class CClassReader;

    class CSourceFileAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CSourceFileAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

    private:
        u2 SourcefileIndex;
    };
}
