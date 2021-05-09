cmake_minimum_required (VERSION 2.8)
project(MeshOrient)

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
