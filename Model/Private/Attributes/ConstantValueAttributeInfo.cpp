//
// Created by ASUS on 05/01/2021.
//

#include "Attributes/ConstantValueAttributeInfo.h"

#include "MemoryFile.h"

namespace Parse
{
    void CConstantValueAttributeInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> ConstantValueIndex;
    }
}