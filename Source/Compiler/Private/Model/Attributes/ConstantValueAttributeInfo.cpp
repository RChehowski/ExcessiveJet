//
// Created by ASUS on 05/01/2021.
//

#include "Model/Attributes/ConstantValueAttributeInfo.h"

#include "Model/ClassReader.h"

namespace Compiler
{
    void CConstantValueAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ConstantValueIndex;
    }
}