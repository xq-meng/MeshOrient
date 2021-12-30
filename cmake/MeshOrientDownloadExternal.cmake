################################################################################
include(DownloadProject)

if(NOT EXTERNAL_DIR)
    set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/extern)
endif()

if(NOT GITHUB_REPOSITE)
    set(GITHUB_REPOSITE "github.com")
endif()

# Shortcut function
function(meshorient_download_project name)
    download_project(
        PROJ         ${name}
        SOURCE_DIR   ${EXTERNAL_DIR}/${name}
        DOWNLOAD_DIR ${EXTERNAL_DIR}/.cache/${name}
        ${ARGN}
    )
endfunction()

################################################################################

## eigen
function(meshorient_download_eigen)
    meshorient_download_project(eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG        3.3.7
    )
endfunction()

## libigl
function(meshorient_download_libigl)
    meshorient_download_project(libigl
        GIT_REPOSITORY  https://github.com/libigl/libigl.git
        GIT_TAG         v2.2.0
    )
endfunction()
