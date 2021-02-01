//
// Created by ASUS on 01/02/2021.
//

#include "Compiler/Model/Public/Attributes/LineNumberTableAttributeInfo.h"

namespace Parse
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