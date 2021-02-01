//
// Created by ASUS on 01/02/2021.
//

#include "MethodInfo.h"

namespace Parse
{
    void operator>>(CClassReader& Reader, CMethodInfo& Instance)
    {
        Reader >> Instance.AccessFlags;
        Reader >> Instance.NameIndex;
        Reader >> Instance.DescriptorIndex;

        Reader >> Instance.Attributes;
    }
}