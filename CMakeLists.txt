cmake_minimum_required(VERSION 3.10)
project(CPP20)

set(CMAKE_CXX_STANDARD 20)

include_directories(Util/Public)
include_directories(Compiler/Bytecode/Public)
include_directories(Model/Public)


set(UnityBuildFiles
    Source/Compiler/Util/Private/_UnityBuild_Util.cpp
    Source/Compiler/Model/Private/_UnityBuild_Model.cpp
    Source/Compiler/Model/Private/Attributes/_UnityBuild_Model_Attributes.cpp
    Source/Compiler/Model/Private/ConstantPool/_UnityBuild_Model_ConstantPool.cpp
)

include_directories(Source)
include_directories(Source/Compiler/Model/Public)
include_directories(Source/Compiler/Util/Public)

add_executable(CPP20
    main.cpp
    "${UnityBuildFiles}"
)
