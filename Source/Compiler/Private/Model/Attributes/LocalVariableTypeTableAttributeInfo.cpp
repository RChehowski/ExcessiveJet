//
// Created by ASUS on 02/02/2021.
//

#include "Model/Attributes/LocalVariableTypeTableAttributeInfo.h"

namespace Compiler
{
    void operator>> (CClassReader& Reader, CLocalVariableTypeTableEntry& Instance)
    {
        Reader >> Instance.StartPc;
        Reader >> Instance.Length;
        Reader >> Instance.NameIndex;
        Reader >> Instance.SignatureIndex;
        Reader >> Instance.Index;
    }

    void CLocalVariableTypeTableAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> LocalVariableTypeTable;
    }
}