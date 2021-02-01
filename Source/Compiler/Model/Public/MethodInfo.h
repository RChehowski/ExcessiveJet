//
// Created by ASUS on 01/02/2021.
//

#pragma once

#include "Types.h"
#include "SerializedArray.h"

namespace Parse
{
    class CClassReader;

    class CAttributeInfo;
    using CSharedAttributeInfo = std::shared_ptr<CAttributeInfo>;

    class CMethodInfo
    {
    public:
        friend void operator>>(CClassReader& Reader, CMethodInfo& Instance);

    private:
        u2 AccessFlags      = (u2)0;
        u2 NameIndex        = (u2)0;
        u2 DescriptorIndex  = (u2)0;

        Util::TStandardSerializedArray<CSharedAttributeInfo> Attributes;
    };
}

