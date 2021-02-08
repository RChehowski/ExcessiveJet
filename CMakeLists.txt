cmake_minimum_required(VERSION 3.10)
project(Excessive)

set(CMAKE_CXX_STANDARD 17)

include_directories(Source/Compiler/Util/Public)
include_directories(Source/Compiler/Bytecode/Public)
include_directories(Source/Compiler/Model/Public)

include_directories(Source/Common)


set(UnityBuildFiles
    Source/Compiler/Util/Private/_UnityBuild_Util.cpp
    Source/Compiler/Model/Private/_UnityBuild_Model.cpp
    Source/Compiler/Model/Private/Debug/_UnityBuild_Model_Debug.cpp
    Source/Compiler/Model/Private/Attributes/_UnityBuild_Model_Attributes.cpp
    Source/Compiler/Model/Private/ConstantPool/_UnityBuild_Model_ConstantPool.cpp
)

include_directories(Source)
include_directories(Source/Compiler/Model/Public)
include_directories(Source/Compiler/Util/Public)

add_subdirectory(third-party/zlib)
include_directories(third-party/zlib)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    "${UnityBuildFiles}"
)

add_dependencies(${CMAKE_PROJECT_NAME} zlibstatic)
target_link_libraries(${CMAKE_PROJECT_NAME} zlibstatic)
