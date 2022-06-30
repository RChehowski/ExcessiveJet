//
// Created by ASUS on 01/02/2021.
//

#include "Model/Attributes/LineNumberTableAttributeInfo.h"

namespace Compiler
{
    void operator>> (CClassReader& Reader, CLineNumberTableAttributeInfoEntry& Instance)
    {
        Reader >> Instance.StartPc;
        Reader >> Instance.LineNumber;
    }

    void CLineNumberTableAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> LineNumberTable;
    }
}