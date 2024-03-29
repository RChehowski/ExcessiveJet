//
// Created by ASUS on 02/02/2021.
//

#include "Model/Attributes/InnerClassesAttributeInfo.h"

namespace Compiler
{
    CClassReader& operator>> (CClassReader& Reader, CInnerClassEntry& Instance)
    {
        Reader >> Instance.InnerClassInfoIndex;
        Reader >> Instance.OuterClassInfoIndex;
        Reader >> Instance.InnerNameIndex;
        Reader >> Instance.InnerClassAccessFlags;

        return Reader;
    }

    void CInnerClassesAttributeInfo::DeserializeFrom(CClassReader& Reader)
    {
        Reader >> Classes;
    }
}