
#pragma once

#include "AttributeInfo.h"
#include "SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Parse
{
    class CClassReader;

    class CLineNumberTableAttributeInfoEntry
    {
        friend void operator>> (CClassReader& Reader, CLineNumberTableAttributeInfoEntry& Instance);

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

        [[nodiscard]]
        FORCEINLINE const TStandardSerializedArray<CLineNumberTableAttributeInfoEntry>& GetLineNumber() const
        {
            return LineNumberTable;
        }

    private:
        TStandardSerializedArray<CLineNumberTableAttributeInfoEntry> LineNumberTable;
    };
}
