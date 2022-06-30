//
// Created by ASUS on 02/02/2021.
//

#pragma once

#include "Model/Attributes/AttributeInfo.h"

using Util::TStandardSerializedArray;

namespace Compiler
{
    class CClassReader;

    class CInnerClassEntry
    {
    public:
        friend CClassReader& operator>> (CClassReader& Reader, CInnerClassEntry& Instance);

    private:
        u2 InnerClassInfoIndex      = (u2)0;
        u2 OuterClassInfoIndex      = (u2)0;
        u2 InnerNameIndex           = (u2)0;
        u2 InnerClassAccessFlags    = (u2)0;
    };

    class CInnerClassesAttributeInfo : public CAttributeInfo
    {
        using Super = CAttributeInfo;
        using Super::Super;

    public:
        ~CInnerClassesAttributeInfo() override = default;

        void DeserializeFrom(CClassReader &Reader) override;

        IMPLEMENT_GET_ATTRIBUTE_INFO_TYPE(InnerClasses);

    private:
        TStandardSerializedArray<CInnerClassEntry> Classes;
    };
}
