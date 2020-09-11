####
# CMakeLists.txt:
#
# Build core F prime.
####
cmake_minimum_required(VERSION 3.5)
project(FPrime-Sphinx-Drivers C CXX)

include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

# Include the build for F prime.
include("${CMAKE_CURRENT_LIST_DIR}/../fprime-vxworks/fprime-vxworks.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/fprime-sphinx-drivers.cmake")
