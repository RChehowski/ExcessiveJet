//
// Created by ASUS on 05/01/2021.
//

#include "Attributes/EnclosingMethodAttributeInfo.h"

#include "ClassReader.h"

namespace Compiler
{
    void CEnclosingMethodAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> MethodIndex;
    }
}