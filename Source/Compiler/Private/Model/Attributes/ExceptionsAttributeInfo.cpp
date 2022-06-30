//
// Created by ASUS on 02/02/2021.
//

#include "Model/Attributes/ExceptionsAttributeInfo.h"

namespace Compiler
{
    void CExceptionsAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> ExceptionIndexTable;
    }
}