//
// Created by ASUS on 01/01/2021.
//

#include "Attributes/LocalVariableTableAttributeInfo.h"

//void operator>> (ClassFileBlob& Blob, CLocalVariable& Instance)
//{
//    Blob >> Instance.StartPC;
//    Blob >> Instance.Length;
//    Blob >> Instance.NameIndex;
//    Blob >> Instance.DescriptorIndex;
//    Blob >> Instance.Index;
//}


//void CLocalVariableTableAttributeInfo::operator>> (ClassFileBlob& Blob)
//{
//    Blob >> LocalVariableTableLength;
//
//    LocalVariableTable = (CLocalVariable*)Memory::MallocT<CLocalVariable>((usz)LocalVariableTableLength);
//
//    for (u2 Offset = 0; Offset < LocalVariableTableLength; ++Offset)
//    {
//        Blob >> LocalVariableTable[Offset];
//    }
//}
