//
// Created by ASUS on 02/05/2021.
//

#pragma once

// Aggregate #include

#include "Model/ConstantPool/ConstantInfo.h"

#include "Model/ConstantPool/ConstantUtf8Info.h"
#include "Model/ConstantPool/ConstantLongInfo.h"
#include "Model/ConstantPool/ConstantFloatInfo.h"
#include "Model/ConstantPool/ConstantClassInfo.h"
#include "Model/ConstantPool/ConstantStringInfo.h"
#include "Model/ConstantPool/ConstantDoubleInfo.h"
#include "Model/ConstantPool/ConstantIntegerInfo.h"
#include "Model/ConstantPool/ConstantFieldRefInfo.h"
#include "Model/ConstantPool/ConstantMethodRefInfo.h"
#include "Model/ConstantPool/ConstantMethodTypeInfo.h"
#include "Model/ConstantPool/ConstantNameAndTypeInfo.h"
#include "Model/ConstantPool/ConstantMethodHandleInfo.h"
#include "Model/ConstantPool/ConstantInvokeDynamicInfo.h"
#include "Model/ConstantPool/ConstantInterfaceMethodRefInfo.h"

/**
 * Import CConstantInfo and all it's subclasses from their namespace.
 */
#define USING_ALL_CONSTANT_INFOS \
    using Compiler::CConstantInfo;\
    using Compiler::CConstantUtf8Info;\
    using Compiler::CConstantLongInfo;\
    using Compiler::CConstantFloatInfo;\
    using Compiler::CConstantClassInfo;\
    using Compiler::CConstantStringInfo;\
    using Compiler::CConstantDoubleInfo;\
    using Compiler::CConstantIntegerInfo;\
    using Compiler::CConstantFieldRefInfo;\
    using Compiler::CConstantMethodRefInfo;\
    using Compiler::CConstantMethodTypeInfo;\
    using Compiler::CConstantNameAndTypeInfo;\
    using Compiler::CConstantMethodHandleInfo;\
    using Compiler::CConstantInvokeDynamicInfo;\
    using Compiler::CConstantInterfaceMethodRefInfo;
