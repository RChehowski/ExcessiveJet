//
// Created by ASUS on 01/01/2021.
//

#pragma once

#include "Types.h"

namespace Util
{
    class CMemoryReader;
}

namespace Parse
{
    class CConstantPool;

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
        FORCEINLINE usz GetAttributeLength() const
        {
            // Expand AttributeLength to usz
            return (usz)AttributeLength;
        }

        virtual void DeserializeFrom(Util::CMemoryReader& Reader) = 0;

    private:
        u2 AttributeNameIndex;
        u4 AttributeLength;
    };

    class CScopeAttributeInfoDeserializeTracker
    {
    public:
        CScopeAttributeInfoDeserializeTracker(CAttributeInfo &InAttributeInfo, Util::CMemoryReader &InReader);

        ~CScopeAttributeInfoDeserializeTracker();

    private:
        const CAttributeInfo& AttributeInfo;
        const Util::CMemoryReader& Reader;

        const usz DeserializeBegin;
    };
}