//
// Created by ASUS on 02/02/2021.
//

#include "Attributes/InnerClassesAttributeInfo.h"

namespace Parse
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