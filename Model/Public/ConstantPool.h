//
// Created by ASUS on 27/12/2020.
//

#pragma once

#include "ConstantPool/ConstantInfo.h"

#include "ConstantPool/ConstantClassInfo.h"
#include "ConstantPool/ConstantDoubleInfo.h"
#include "ConstantPool/ConstantFieldRefInfo.h"
#include "ConstantPool/ConstantFloatInfo.h"
#include "ConstantPool/ConstantIntegerInfo.h"
#include "ConstantPool/ConstantInterfaceMethodRefInfo.h"
#include "ConstantPool/ConstantInvokeDynamicInfo.h"
#include "ConstantPool/ConstantLongInfo.h"
#include "ConstantPool/ConstantMethodHandleInfo.h"
#include "ConstantPool/ConstantMethodRefInfo.h"
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "ConstantPool/ConstantNameAndTypeInfo.h"
#include "ConstantPool/ConstantStringInfo.h"
#include "ConstantPool/ConstantUtf8Info.h"

#include "Assert.h"


namespace Parse
{
    class CConstantPool
    {
    public:
    };

    CConstantInfo* New_ConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag);

    template <typename T>
    T* Cast_ConstantInfo(CConstantInfo* const ConstantInfo)
    {
        static_assert(std::is_base_of_v<CConstantInfo, T>, "T must be a subclass of CConstantInfo");

        if (ConstantInfo->GetConstantPoolInfoTag() == T::StaticTag)
        {
            return reinterpret_cast<T*>(ConstantInfo);
        }
        else
        {
            ASSERT(false);
            return nullptr;
        }
    }
}
