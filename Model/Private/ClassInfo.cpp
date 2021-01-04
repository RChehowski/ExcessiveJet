//
// Created by ASUS on 03/01/2021.
//

#include "ClassInfo.h"
#include "MemoryFile.h"

namespace Parse
{
    void operator>>(Util::CMemoryReader& Reader, CInterfaces& Instance)
    {
        u2 InterfacesCount = (u2) 0;
        Reader >> InterfacesCount;

        Instance.clear();
        Instance.reserve((size_t)InterfacesCount);

        for (u2 InterfaceIndex = 0; InterfaceIndex < InterfacesCount; InterfaceIndex++)
        {
            u2 Interface = (u2)0;
            Reader >> Interface;

            Instance.push_back(Interface);
        }
    }

    void operator>>(Util::CMemoryReader& Reader, CClassInfo& Instance)
    {
        Reader >> Instance.Magic;
        Reader >> Instance.MinorVersion;
        Reader >> Instance.MajorVersion;

        Reader >> Instance.ConstantPool;

        Reader >> Instance.AccessFlags;
        Reader >> Instance.ThisClass;
        Reader >> Instance.SuperClass;

        Reader >> Instance.Interfaces;


    }
}