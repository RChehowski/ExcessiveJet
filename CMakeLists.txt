cmake_minimum_required(VERSION 3.17)
project(CPP20)

set(CMAKE_CXX_STANDARD 20)

include_directories(Util/Public)
include_directories(Bytecode/Public)
include_directories(ClassParser/Public)

add_executable(CPP20 main.cpp Sample.h ClassParser/Private/CConstantPool.cpp ClassParser/Public/CConstantPool.h ClassParser/Private/ParsedClass.cpp ClassParser/Public/ParsedClass.h Util/Private/MemoryFile.cpp Util/Public/MemoryFile.h Util/Private/Platform/FileUtils.cpp Util/Public/Platform/FileUtils.h Util/Public/Types.h Util/Private/Platform/Memory.cpp Util/Public/Platform/Memory.h Util/Private/Platform/Misc.cpp Util/Public/Platform/Misc.h Util/Private/StringUtf8.cpp Util/Public/StringUtf8.h Bytecode/Public/Opcodes.h Util/Public/Assert.h Bytecode/Private/Opcodes.cpp ClassParser/Private/Attributes.cpp ClassParser/Public/Attributes.h ClassParser/Public/Attributes/AttributeInfo.h ClassParser/Public/Attributes/LocalVariableTableAttributeInfo.h ClassParser/Private/Attributes/LocalVariableTableAttributeInfo.cpp Util/Public/MathUtils.h)
