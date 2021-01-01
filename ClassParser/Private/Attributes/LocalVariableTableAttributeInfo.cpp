//
// Created by ASUS on 01/01/2021.
//

#include "Attributes/LocalVariableTableAttributeInfo.h"

void operator>> (ClassFileBlob& Blob, CLocalVariable& Instance)
{
    Blob >> Instance.StartPC;
    Blob >> Instance.Length;
    Blob >> Instance.NameIndex;
    Blob >> Instance.DescriptorIndex;
    Blob >> Instance.Index;
}


void operator>> (ClassFileBlob& Blob, CLocalVariableTableAttributeInfo& Instance)
{
    Blob >> Instance.LocalVariableTableLength;

    Instance.LocalVariableTable =
            (CLocalVariable*)Memory::MallocT<CLocalVariable>((size_t)Instance.LocalVariableTableLength);

    for (u2 Offset = 0; Offset < Instance.LocalVariableTableLength; ++Offset)
    {
        CLocalVariable& LocalVariable = Instance.LocalVariableTable[Offset];
        Blob >> LocalVariable;
    }
}
