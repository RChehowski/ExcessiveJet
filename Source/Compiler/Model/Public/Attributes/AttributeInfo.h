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

    class CAttributeInfoHeader
    {
    public:
        CAttributeInfoHeader() = default;
        ~CAttributeInfoHeader() = default;

        friend Util::CMemoryReader& operator>> (Util::CMemoryReader& Reader, CAttributeInfoHeader& Instance);

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

    private:
        u2 AttributeNameIndex   = (u2)0;
        u4 AttributeLength      = (u4)0;
    };

    class CAttributeInfo
    {
    public:
        virtual ~CAttributeInfo() = default;

        virtual void DeserializeFrom(CClassReader& Reader) = 0;
    };

    using CSharedAttributeInfo = std::shared_ptr<CAttributeInfo>;

    CClassReader& operator>>(CClassReader& Reader, Util::TStandardSerializedArray<CSharedAttributeInfo>& Instance);
}