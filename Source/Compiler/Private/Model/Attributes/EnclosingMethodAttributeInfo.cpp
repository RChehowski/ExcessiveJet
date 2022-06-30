//
// Created by ASUS on 05/01/2021.
//

#include "Model/Attributes/EnclosingMethodAttributeInfo.h"
#include "Model/ClassReader.h"

namespace Compiler
{
    void CEnclosingMethodAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> ClassIndex;
        Reader >> MethodIndex;
    }
}