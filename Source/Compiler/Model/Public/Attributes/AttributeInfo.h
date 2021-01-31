//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Types.h"
#include "SerializedArray.h"

namespace Parse
{
    class CClassReader;
    class CConstantPool;

    class CAttributeInfo : public TSharedFromThis<CAttributeInfo>
    {
    public:
        virtual ~CAttributeInfo() = default;

        virtual void DeserializeBody(CClassReader& Reader) = 0;

        friend CClassReader& operator>>(CClassReader& Reader, CAttributeInfo& Instance);
    };

    using CSharedAttributeInfo = std::shared_ptr<CAttributeInfo>;

    CClassReader& operator>>(CClassReader& Reader, Util::TStandardSerializedArray<CSharedAttributeInfo>& Instance);
}