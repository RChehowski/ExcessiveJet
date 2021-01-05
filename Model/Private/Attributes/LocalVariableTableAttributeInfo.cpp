//
// Created by ASUS on 01/01/2021.
//

#include "Attributes/LocalVariableTableAttributeInfo.h"

#include "MemoryFile.h"

namespace Parse
{
    void operator>> (Util::CMemoryReader& Reader, CLocalVariable& Instance)
    {
        Reader >> Instance.StartPC;
        Reader >> Instance.Length;
        Reader >> Instance.NameIndex;
        Reader >> Instance.DescriptorIndex;
        Reader >> Instance.Index;
    }

    void CLocalVariableTableAttributeInfo::DeserializeFrom(Util::CMemoryReader& Reader)
    {
        Reader >> LocalVariableTable;
    }
}
