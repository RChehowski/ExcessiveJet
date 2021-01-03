//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Types.h"

class ClassFileBlob;

class CAttributeInfo
{
public:
    FORCEINLINE CAttributeInfo(u2 InAttributeNameIndex, u4 InAttributeLength)
        : AttributeNameIndex(InAttributeNameIndex)
        , AttributeLength(InAttributeLength)
    {
    }

    virtual ~CAttributeInfo() = default;

    [[nodiscard]]
    FORCEINLINE u2 GetAttributeNameIndex() const
    {
        return AttributeNameIndex;
    }

    [[nodiscard]]
    FORCEINLINE u4 GetAttributeLength() const
    {
        return AttributeLength;
    }

    virtual void operator>> (ClassFileBlob& Blob) = 0;

private:
    const u2 AttributeNameIndex;
    const u4 AttributeLength;
};