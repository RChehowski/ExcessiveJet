//
// Created by ASUS on 03/01/2021.
//

#pragma once

#include "Types.h"
#include "ConstantPool.h"

#include "FieldInfo.h"

#include "SerializedArray.h"

namespace Parse
{
    class CClassReader;

    enum class EClassInfoDeserializingMode : u1
    {
        ConstantPool,

        All = std::numeric_limits<u1>::max()
    };

    class CClassInfo
    {
    public:
        void Deserialize(CClassReader& Reader,
                         EClassInfoDeserializingMode ClassInfoDeserializingMode = EClassInfoDeserializingMode::All
        );

        FORCEINLINE friend void operator>>(CClassReader& Reader, CClassInfo& Instance)
        {
            Instance.Deserialize(Reader, EClassInfoDeserializingMode::All);
        }

    private:
        u4 Magic = (u4) 0;
        u2 MinorVersion = (u2) 0;
        u2 MajorVersion = (u2) 0;

        std::shared_ptr<CConstantPool> ConstantPool = std::make_shared<CConstantPool>();

        u2 AccessFlags = (u2)0;
        u2 ThisClass = (u2)0;
        u2 SuperClass = (u2)0;

        Util::TStandardSerializedArray<u2> Interfaces;

        Util::TStandardSerializedArray<CFieldInfo> Fields;
    };
}
