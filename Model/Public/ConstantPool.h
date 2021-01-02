//
// Created by ASUS on 27/12/2020.
//

#pragma once

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

#include "StringUtf8.h"

namespace Parse
{
    CConstantInfo* GetConstantInfo(EConstantPoolInfoTag ConstantPoolInfoTag);
}
