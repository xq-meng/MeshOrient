###############################################################################
# CMake download helpers
###############################################################################

# download external dependencies
include(MeshOrientDownloadExternal)

###############################################################################
# Required dependencies
###############################################################################

# eigen
if(NOT EIGEN_BASE)
    meshorient_download_eigen()
    set(EIGEN_BASE ${EXTERNAL_DIR}/eigen)
endif()
