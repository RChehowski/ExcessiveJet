//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "Util/SerializedArray.h"

using Util::TStandardSerializedArray;

namespace Compiler
{
    class CClassReader;

    class CExceptionsAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CExceptionsAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(Exceptions);

    private:
        TStandardSerializedArray<u2> ExceptionIndexTable;
    };
}
