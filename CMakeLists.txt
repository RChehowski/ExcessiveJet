cmake_minimum_required(VERSION 3.17)
project(CPP20)

set(CMAKE_CXX_STANDARD 20)

include_directories(Util/Public)
include_directories(Bytecode/Public)
include_directories(ClassParser/Public)

add_executable(CPP20
    main.cpp
    ClassParser/Private/CConstantPool.cpp
    ClassParser/Private/ParsedClass.cpp
    Util/Private/MemoryFile.cpp
    Util/Private/Platform/FileUtils.cpp
    Util/Private/Platform/Memory.cpp
    Util/Private/Platform/Misc.cpp
    Util/Private/StringUtf8.cpp
    Bytecode/Private/Opcodes.cpp
    ClassParser/Private/Attributes.cpp
    ClassParser/Private/Attributes/LocalVariableTableAttributeInfo.cpp
)
