//
// Created by ASUS on 02/02/2021.
//

#include "Attributes/ExceptionsAttributeInfo.h"

namespace Parse
{
    void CExceptionsAttributeInfo::DeserializeFrom(CClassReader &Reader)
    {
        Reader >> ExceptionIndexTable;
    }
}