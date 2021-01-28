//
// Created by ASUS on 03/01/2021.
//

#include "FieldInfo.h"
#include "ClassReader.h"

namespace Parse
{
    void CFieldInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> AccessFlags;
        Reader >> NameIndex;
        Reader >> DescriptorIndex;
        Reader >> Attributes;
    }

    void operator>>(CClassReader& Reader, CFieldInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}