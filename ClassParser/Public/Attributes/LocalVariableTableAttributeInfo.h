//
// Created by ASUS on 01/01/2021.
//

#pragma once


#include "Attributes/AttributeInfo.h"

#include "Assert.h"
#include "Platform/Memory.h"

// TODO: Delete
#include "CConstantPool.h"

using Util::Memory;

struct CLocalVariable
{
    friend void operator>> (ClassFileBlob& Blob, CLocalVariable& Instance);

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

private:
    u2 StartPC;
    u2 Length;
    u2 NameIndex;
    u2 DescriptorIndex;
    u2 Index;
};


struct CLocalVariableTableAttributeInfo : public CAttributeInfo
{
    using Super = CAttributeInfo;
    using Super::Super;

public:
    FORCEINLINE ~CLocalVariableTableAttributeInfo() override
    {
        Memory::Free(LocalVariableTable);
    }

    [[nodiscard]]
    FORCEINLINE const CLocalVariable* GetLocalVariable(usz Index) const
    {
        ASSERT(Index < (usz)LocalVariableTableLength);
        return LocalVariableTable + Index;
    }

    [[nodiscard]]
    FORCEINLINE u2 GetLocalVariableTableLength() const
    {
        return LocalVariableTableLength;
    }

    void operator>> (ClassFileBlob& Blob) override;

    FORCEINLINE static CAttributeInfo* NewInstance(u2 InAttributeNameIndex, u4 InAttributeLength)
    {
        return new CLocalVariableTableAttributeInfo(InAttributeNameIndex, InAttributeLength);
    }

private:
    u2 LocalVariableTableLength;
    CLocalVariable* LocalVariableTable = nullptr;
};
