cmake_minimum_required (VERSION 2.8)
project(MeshOrient)

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()

option(BUILD_EXECUTABLE "Build executable." ON)

set(SOURCES
include/MeshOrient.h
src/triMesh.h
src/MeshOrient.cpp)
add_library(MeshOrient STATIC ${SOURCES})
target_include_directories(MeshOrient PRIVATE ./extern/eigen)
target_include_directories(MeshOrient PUBLIC ./include)

if(BUILD_EXECUTABLE)
    add_executable(MeshOrientExe src/MeshOrientExe.cpp)
    target_link_libraries(MeshOrientExe PUBLIC MeshOrient)
    set_target_properties(MeshOrientExe PROPERTIES OUTPUT_NAME MeshOrient)
endif()
