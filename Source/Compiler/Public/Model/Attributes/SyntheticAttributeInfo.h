//
// Created by ASUS on 05/01/2021.
//

#pragma once

#include "AttributeInfo.h"
#include "Model/ClassReader.h"


class CClassReader;

namespace Compiler
{
    class CSyntheticAttributeInfo final : public CAttributeInfo
    {
    public:
        void DeserializeFrom(CClassReader& Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(Synthetic);
    };
}
