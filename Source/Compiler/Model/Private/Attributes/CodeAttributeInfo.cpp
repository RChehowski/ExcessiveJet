//
// Created by ASUS on 10/01/2021.
//

#include "Attributes/CodeAttributeInfo.h"

namespace Parse
{
    CClassReader& operator>>(CClassReader& Reader, CExceptionTableEntry& Instance)
    {
        Reader >> Instance.StartPc;
        Reader >> Instance.EndPc;
        Reader >> Instance.HandlerPc;
        Reader >> Instance.CatchType;

        return Reader;
    }

    void CCodeAttributeInfo::DeserializeBody(CClassReader& Reader)
    {
        Reader >> MaxStack;
        Reader >> MaxLocals;
        Reader >> Code;
        Reader >> ExceptionTable;
        Reader >> Attributes;
    }
}