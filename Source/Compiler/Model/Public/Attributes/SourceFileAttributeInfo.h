//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "Attributes/AttributeInfo.h"

namespace Compiler
{
    class CClassReader;

    class CSourceFileAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CSourceFileAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(SourceFile);

        [[nodiscard]]
        FORCEINLINE u2 GetSourcefileIndex() const
        {
            return SourcefileIndex;
        }

    private:
        u2 SourcefileIndex;
    };
}
