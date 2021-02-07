//
// Created by ASUS on 01/01/2021.
//

#pragma once


#include "Attributes/AttributeInfo.h"

#include "Assert.h"
#include "SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Parse
{
    class CClassReader;

    class CLocalVariableTypeTableEntry
    {
    public:
        friend void operator>> (CClassReader& Reader, CLocalVariableTypeTableEntry& Instance);

    private:
        u2 StartPc          = (u2)0;
        u2 Length           = (u2)0;
        u2 NameIndex        = (u2)0;
        u2 SignatureIndex   = (u2)0;
        u2 Index            = (u2)0;
    };

    class CLocalVariableTypeTableAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        void DeserializeFrom(CClassReader& Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(LocalVariableTypeTable);

    private:
        TStandardSerializedArray<CLocalVariableTypeTableEntry> LocalVariableTypeTable;
    };
}