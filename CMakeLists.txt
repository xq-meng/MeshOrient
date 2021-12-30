cmake_minimum_required (VERSION 2.8.12)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
project(MeshOrient)
if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release")
endif()
# options
option(MESHORIENT_BUILD_EXECUTABLE "Build executable." ON)
# download
if(DOWNLOAD_WITH_CNPM)
    set (GITHUB_REPOSITE "github.com.cnpmjs.org")
elseif(DOWNLOAD_WITH_GITCLONE)
    set (GITHUB_REPOSITE "gitclone.com/github.com")
else()
    set (GITHUB_REPOSITE "github.com")
endif()
include(MeshOrientDependencies)
set(SOURCES
include/MeshOrient.h
src/triMesh.h
src/triMesh.cpp
src/MeshOrient.cpp)
add_library(MeshOrient STATIC ${SOURCES})
target_include_directories(MeshOrient PUBLIC ${EIGEN_BASE})
target_include_directories(MeshOrient PUBLIC ${IGL_BASE}/include)
target_include_directories(MeshOrient PUBLIC ./include)
target_link_libraries(MeshOrient PUBLIC pthread)

if(MESHORIENT_BUILD_EXECUTABLE)
    add_executable(MeshOrientExe src/MeshOrientExe.cpp)
    target_link_libraries(MeshOrientExe PUBLIC MeshOrient)
    set_target_properties(MeshOrientExe PROPERTIES OUTPUT_NAME MeshOrient)
endif()
