//
// Created by ASUS on 02/05/2021.
//

#pragma once

// Aggregate #include

#include "ConstantPool/ConstantInfo.h"

#include "ConstantPool/ConstantUtf8Info.h"
#include "ConstantPool/ConstantLongInfo.h"
#include "ConstantPool/ConstantFloatInfo.h"
#include "ConstantPool/ConstantClassInfo.h"
#include "ConstantPool/ConstantStringInfo.h"
#include "ConstantPool/ConstantDoubleInfo.h"
#include "ConstantPool/ConstantIntegerInfo.h"
#include "ConstantPool/ConstantFieldRefInfo.h"
#include "ConstantPool/ConstantMethodRefInfo.h"
#include "ConstantPool/ConstantMethodTypeInfo.h"
#include "ConstantPool/ConstantNameAndTypeInfo.h"
#include "ConstantPool/ConstantMethodHandleInfo.h"
#include "ConstantPool/ConstantInvokeDynamicInfo.h"
#include "ConstantPool/ConstantInterfaceMethodRefInfo.h"

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
