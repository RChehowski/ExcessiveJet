//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Parse
{
    class CClassReader;

    class CExceptionsAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CExceptionsAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

    private:
        TStandardSerializedArray<u2> ExceptionIndexTable;
    };
}
