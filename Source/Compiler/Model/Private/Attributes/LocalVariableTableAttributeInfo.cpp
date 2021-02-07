//
// Created by ASUS on 01/01/2021.
//

#include "Attributes/LocalVariableTableAttributeInfo.h"

#include "ClassReader.h"

namespace Compiler
{
    void operator>> (CClassReader& Reader, CLocalVariable& Instance)
    {
        Reader >> Instance.StartPC;
        Reader >> Instance.Length;
        Reader >> Instance.NameIndex;
        Reader >> Instance.DescriptorIndex;
        Reader >> Instance.Index;
    }

    void CLocalVariableTableAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> LocalVariableTable;
    }
}
