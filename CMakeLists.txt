cmake_minimum_required(VERSION 3.10)
project(Excessive)

set(CMAKE_CXX_STANDARD 17)



include_directories(Source)
include_directories(Source/Common/Public)
include_directories(Source/Compiler/Public)

include_directories(third-party)
include_directories(third-party/rpmalloc)

set(UnityBuildFiles
#    third-party/rpmalloc/malloc.c
    third-party/rpmalloc/rpmalloc.c

    Source/Common/Private/_Unity_Common_.cpp
    Source/Compiler/Private/_Unity_Compiler_.cpp
)



add_executable(${CMAKE_PROJECT_NAME} main.cpp "${UnityBuildFiles}")
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC ENABLE_STATISTICS=1)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC UNLOCK_DEBUG_METHODS=1)
target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_WITH_LOCAL_VARIABLES_DEBUG_INFO=1)

if (WIN32 )
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PLATFORM_WINDOWS=1)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PLATFORM_UNIX=0)
endif (WIN32)
if (UNIX)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PLATFORM_UNIX=1)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC PLATFORM_WINDOWS=0)
endif (UNIX)
if (MSVC)
    # do something
endif (MSVC)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_64=1)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_32=0)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_64=0)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_32=1)
else()
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_64=0)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC EXJ_32=0)
endif()