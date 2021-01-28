//
// Created by ASUS on 03/01/2021.
//

#include <iostream>
#include "ClassInfo.h"
#include "ClassReader.h"

namespace Parse
{
    void operator>>(CClassReader& Reader, CClassInfo& Instance)
    {
        Reader >> Instance.Magic;
        Reader >> Instance.MinorVersion;
        Reader >> Instance.MajorVersion;

        Reader >> Instance.ConstantPool;
        Reader.SetConstantPool(&(Instance.ConstantPool));

        Reader >> Instance.AccessFlags;
        Reader >> Instance.ThisClass;
        Reader >> Instance.SuperClass;

//        Reader >> Instance.Interfaces;
//        Reader >> Instance.Fields;

        std::cout << "Hello";
    }
}