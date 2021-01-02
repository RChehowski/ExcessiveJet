cmake_minimum_required(VERSION 3.10)
project(CPP20)

set(CMAKE_CXX_STANDARD 20)

include_directories(Util/Public)
include_directories(Bytecode/Public)
include_directories(Model/Public)

set(ConstantPoolConstants
    Model/Private/ConstantPool/ConstantClassInfo.cpp
    Model/Private/ConstantPool/ConstantDoubleInfo.cpp
    Model/Private/ConstantPool/ConstantFieldRefInfo.cpp
    Model/Private/ConstantPool/ConstantFloatInfo.cpp
    Model/Private/ConstantPool/ConstantIntegerInfo.cpp
    Model/Private/ConstantPool/ConstantInterfaceMethodRefInfo.cpp
    Model/Private/ConstantPool/ConstantInvokeDynamicInfo.cpp
    Model/Private/ConstantPool/ConstantLongInfo.cpp
    Model/Private/ConstantPool/ConstantMethodHandleInfo.cpp
    Model/Private/ConstantPool/ConstantMethodRefInfo.cpp
    Model/Private/ConstantPool/ConstantMethodTypeInfo.cpp
    Model/Private/ConstantPool/ConstantNameAndTypeInfo.cpp
    Model/Private/ConstantPool/ConstantStringInfo.cpp
    Model/Private/ConstantPool/ConstantUtf8Info.cpp
)

add_executable(CPP20
    main.cpp
        Model/Private/ConstantPool.cpp
    Model/Private/ParsedClass.cpp
    Util/Private/MemoryFile.cpp
    Util/Private/Platform/FileUtils.cpp
    Util/Private/Platform/Memory.cpp
    Util/Private/Platform/Misc.cpp
    Util/Private/StringUtf8.cpp
    Bytecode/Private/Opcodes.cpp
    Model/Private/Attributes.cpp
    Model/Private/Attributes/LocalVariableTableAttributeInfo.cpp
    Model/Private/ConstantPool/ConstantClassInfo.cpp
    Model/Private/ConstantPool/ConstantFieldrefInfo.cpp
    Model/Private/ConstantPool/ConstantMethodrefInfo.cpp
    Model/Private/ConstantPool/ConstantInterfaceMethodrefInfo.cpp
    ${ConstantPoolConstants}
)
