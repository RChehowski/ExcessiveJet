//
// Created by ASUS on 10/01/2021.
//

#pragma once

#include "Attributes/AttributeInfo.h"

#include "ByteBuffer.h"
#include "SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Parse
{
    class CExceptionTableEntry
    {
    public:
        [[nodiscard]]
        FORCEINLINE u2 GetStartPc() const
        {
            return StartPc;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetEndPc() const
        {
            return EndPc;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetHandlerPc() const
        {
            return HandlerPc;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetCatchType() const
        {
            return CatchType;
        }

        // Must implement operator>> to be deserialized
        friend CClassReader& operator>> (CClassReader& Reader, CExceptionTableEntry& Instance);

    private:
        u2 StartPc      = (u2)0;
        u2 EndPc        = (u2)0;
        u2 HandlerPc    = (u2)0;
        u2 CatchType    = (u2)0;
    };

    class CCodeAttributeInfo : public CAttributeInfo
    {
        using CAttributeInfo::CAttributeInfo;

    public:
        void DeserializeFrom(CClassReader &Reader) override;

        [[nodiscard]]
        FORCEINLINE u2 GetMaxStack() const
        {
            return MaxStack;
        }

        [[nodiscard]]
        FORCEINLINE u2 GetMaxLocals() const
        {
            return MaxLocals;
        }

        [[nodiscard]]
        FORCEINLINE const TStandardSerializedArray<u1>& GetCode() const
        {
            return Code;
        }

        [[nodiscard]]
        FORCEINLINE const TStandardSerializedArray<CExceptionTableEntry>& GetExceptionTable() const
        {
            return ExceptionTable;
        }

        [[nodiscard]]
        FORCEINLINE const TStandardSerializedArray<CSharedAttributeInfo>& GetAttributes() const
        {
            return Attributes;
        }

    private:
        u2 MaxStack    = (u2)0;
        u2 MaxLocals   = (u2)0;

        TStandardSerializedArray<u1> Code = {};

        TStandardSerializedArray<CExceptionTableEntry> ExceptionTable = {};

        TStandardSerializedArray<CSharedAttributeInfo> Attributes = {};
    };
}
