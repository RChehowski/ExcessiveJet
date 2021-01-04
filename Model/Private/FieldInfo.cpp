//
// Created by ASUS on 03/01/2021.
//

#include "FieldInfo.h"

#include "MemoryFile.h"

namespace Parse
{
    void CFieldInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> AccessFlags;
        Reader >> NameIndex;
        Reader >> DescriptorIndex;
        Reader >> AttributesCount;
    }

    void operator>>(Util::CMemoryReader& Reader, CFieldInfo& Instance)
    {
        Instance.DeserializeFrom(Reader);
    }
}