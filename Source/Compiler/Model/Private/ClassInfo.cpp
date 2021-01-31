//
// Created by ASUS on 03/01/2021.
//

#include <iostream>
#include "ClassInfo.h"
#include "ClassReader.h"

namespace Parse
{
    void CClassInfo::Deserialize(CClassReader& Reader,
                                 EClassInfoDeserializingMode ClassInfoDeserializingMode
    )
    {
        Reader >> Magic;
        Reader >> MinorVersion;
        Reader >> MajorVersion;

        ConstantPool = std::make_shared<CConstantPool>();
        Reader >> *(ConstantPool.get());
        Reader.SetConstantPool(ConstantPool);

        Reader >> AccessFlags;
        Reader >> ThisClass;
        Reader >> SuperClass;

//        Reader >> Instance.Interfaces;
//        Reader >> Instance.Fields;

        std::cout << "Hello";
    }
}