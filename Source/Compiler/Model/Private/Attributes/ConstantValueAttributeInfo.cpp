//
// Created by ASUS on 05/01/2021.
//

#include "Attributes/ConstantValueAttributeInfo.h"

#include "ClassReader.h"

namespace Parse
{
    void CConstantValueAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ConstantValueIndex;
    }
}