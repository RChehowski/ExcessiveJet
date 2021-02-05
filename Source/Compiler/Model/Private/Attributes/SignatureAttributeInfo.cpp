//
// Created by ASUS on 02/02/2021.
//

#include "Attributes/SignatureAttributeInfo.h"

namespace Parse
{
    void CSignatureAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> SignatureIndex;
    }
}