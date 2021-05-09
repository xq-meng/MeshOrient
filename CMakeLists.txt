cmake_minimum_required (VERSION 2.8)
project(MeshOrient)

option(BUILD_EXECUTABLE "Build executable." ON)

set(SOURCES
include/MeshOrient.h
src/triMesh.h
src/MeshOrient.cpp)
add_library(MeshOrient STATIC ${SOURCES})
target_include_directories(MeshOrient PUBLIC ./include)
target_include_directories(MeshOrient PRIVATE ./extern/eigen)

if(BUILD_EXECUTABLE)
    add_executable(MeshOrientExe src/MeshOrientExe.cpp)
    target_link_libraries(MeshOrientExe PUBLIC TIGER::MeshOrient)
    set_target_properties(MeshOrientExe PROPERTIES OUTPUT_NAME MeshOrient)
endif()
