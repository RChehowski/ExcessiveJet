
#pragma once

#include "AttributeInfo.h"
#include "Util/SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Compiler
{
    class CClassReader;

    class CLineNumberTableAttributeInfoEntry
    {
        friend void operator>> (CClassReader& Reader, CLineNumberTableAttributeInfoEntry& Instance);

    public:
        [[nodiscard]]
        FORCEINLINE u2 GetStartPc() const
        {
            return StartPc;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetLineNumber() const
        {
            return LineNumber;
        }

    private:
        u2 StartPc      = (u2)0;
        u2 LineNumber   = (u2)0;
    };

    class CLineNumberTableAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CLineNumberTableAttributeInfo() override = default;

        void DeserializeFrom(CClassReader& Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(LineNumberTable);

        [[nodiscard]]
        FORCEINLINE const TStandardSerializedArray<CLineNumberTableAttributeInfoEntry>& GetLineNumberTable() const
        {
            return LineNumberTable;
        }

    private:
        TStandardSerializedArray<CLineNumberTableAttributeInfoEntry> LineNumberTable;
    };
}
