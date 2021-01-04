//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Types.h"
#include "ConstantPool.h"

namespace Parse
{
    using CInterfaces = std::vector<u2>;

    void operator>>(Util::CMemoryReader& Reader, CInterfaces& Instance);

    class CClassInfo
    {
    public:
        friend void operator>>(Util::CMemoryReader& Reader, CClassInfo& Instance);

    private:
        u4 Magic = (u4) 0;
        u2 MinorVersion = (u2) 0;
        u2 MajorVersion = (u2) 0;

        CConstantPool ConstantPool;

        u2 AccessFlags = (u2)0;
        u2 ThisClass = (u2)0;
        u2 SuperClass = (u2)0;

        CInterfaces Interfaces;
    };
}
