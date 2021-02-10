//
// Created by ASUS on 01/01/2021.
//

#pragma once


#include "Attributes/AttributeInfo.h"

#include "ExcessiveAssert.h"
#include "SerializedArray.h"


namespace Compiler
{
    class CClassReader;

    class CLocalVariable
    {
    public:
        [[nodiscard]]
        FORCEINLINE u2 GetStartPc() const
        {
            return StartPC;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetLength() const
        {
            return Length;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetNameIndex() const
        {
            return NameIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetDescriptorIndex() const
        {
            return DescriptorIndex;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetIndex() const
        {
            return Index;
        }

        // Must implement operator>> to be deserialized
        friend void operator>> (CClassReader& Reader, CLocalVariable& Instance);

    private:
        u2 StartPC;
        u2 Length;
        u2 NameIndex;
        u2 DescriptorIndex;
        u2 Index;
    };

    class CLocalVariableTableAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        [[nodiscard]]
        FORCEINLINE const Util::TSerializedArray<u2, CLocalVariable>& GetLocalVariableTable() const
        {
            return LocalVariableTable;
        }

        void DeserializeFrom(CClassReader& Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(LocalVariableTable);

    private:
        Util::TSerializedArray<u2, CLocalVariable> LocalVariableTable;
    };
}