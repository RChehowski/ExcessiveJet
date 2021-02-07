//
// Created by ASUS on 02/02/2021.
//

#include "Attributes/SourceFileAttributeInfo.h"

namespace Compiler
{
    void CSourceFileAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> SourcefileIndex;
    }
}