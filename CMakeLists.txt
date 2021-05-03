cmake_minimum_required(VERSION 3.10)
project(Excessive)

set(CMAKE_CXX_STANDARD 17)

include_directories(Source/Compiler/Util/Public)
include_directories(Source/Compiler/Bytecode/Public)
include_directories(Source/Compiler/Model/Public)
include_directories(Source/Common/Filesystem/Zip/Public)
include_directories(Source/Common/Util/Public)

include_directories(Source/Common)

include_directories(third-party)

set(UnityBuildFiles
    Source/Compiler/Util/Private/_UnityBuild_Util.cpp
    Source/Compiler/Model/Private/_UnityBuild_Model.cpp
    Source/Compiler/Model/Private/Debug/_UnityBuild_Model_Debug.cpp
    Source/Compiler/Model/Private/Attributes/_UnityBuild_Model_Attributes.cpp
    Source/Compiler/Model/Private/ConstantPool/_UnityBuild_Model_ConstantPool.cpp

    Source/Common/Util/Private/_UnityBuild_Common_Util.cpp

    # Common
    Source/Common/Service/Private/_UnityBuild_Service.cpp Source/Compiler/Printer/CppPrinter.cpp Source/Compiler/Printer/CppPrinter.h Source/Runtime/ObjectBase.cpp Source/Runtime/ObjectBase.h Source/Runtime/CMeta.cpp Source/Runtime/CMeta.h)

include_directories(Source)
include_directories(Source/Compiler/Model/Public)
include_directories(Source/Compiler/Util/Public)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    "${UnityBuildFiles}"
)
