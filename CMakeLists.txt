cmake_minimum_required(VERSION 3.10)
project(Excessive)

set(CMAKE_CXX_STANDARD 17)


include_directories(Source/Common/Public)
include_directories(Source/Compiler/Public)

include_directories(third-party)
include_directories(third-party/rpmalloc)

set(UnityBuildFiles
    third-party/rpmalloc/malloc.c
    third-party/rpmalloc/rpmalloc.c

    Source/Common/Private/_Unity_Common_.cpp
    Source/Compiler/Private/_Unity_Compiler_.cpp
)

include_directories(Source)

add_executable(${CMAKE_PROJECT_NAME} main.cpp "${UnityBuildFiles}")
