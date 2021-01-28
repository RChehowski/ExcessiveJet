//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Types.h"
#include "ConstantPool.h"

#include "FieldInfo.h"

#include "SerializedArray.h"
#include "ClassReader.h"

namespace Parse
{
    class CClassInfo
    {
    public:
        friend void operator>>(CClassReader& Reader, CClassInfo& Instance);

    private:
        u4 Magic = (u4) 0;
        u2 MinorVersion = (u2) 0;
        u2 MajorVersion = (u2) 0;

        CConstantPool ConstantPool;

        u2 AccessFlags = (u2)0;
        u2 ThisClass = (u2)0;
        u2 SuperClass = (u2)0;

        Util::TStandardSerializedArray<u2> Interfaces;

        Util::TStandardSerializedArray<CFieldInfo> Fields;
    };
}
