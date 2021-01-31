//
// Created by ASUS on 03/01/2021.
//

#include <iostream>
#include "ClassInfo.h"
#include "ClassReader.h"

namespace Parse
{
    void CClassInfo::Deserialize(CClassReader& Reader, EClassInfoDeserializingMode ClassInfoDeserializingMode)
    {
        Reader >> Magic;
        ASSERT(Magic == 0xCAFEBABE);

        Reader >> MinorVersion;
        Reader >> MajorVersion;

        Reader >> ConstantPool;
        Reader.SetConstantPool(ConstantPool);

        Reader >> AccessFlags;
        Reader >> ThisClass;
        Reader >> SuperClass;

//        Reader >> Instance.Interfaces;
//        Reader >> Instance.Fields;
    }
}