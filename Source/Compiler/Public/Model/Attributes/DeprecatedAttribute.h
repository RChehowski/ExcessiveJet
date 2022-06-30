//
// Created by ASUS on 18/01/2021.
//

#pragma once

#include "Model/Attributes/AttributeInfo.h"

namespace Compiler
{
    class CDeprecatedAttributeInfo : public CAttributeInfo
    {
    public:
        ~CDeprecatedAttributeInfo() override
        {
        }

        void DeserializeFrom(CClassReader &Reader) override
        {
        }

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(Deprecated);
    };
}
