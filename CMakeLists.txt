cmake_minimum_required(VERSION 2.8.3)

project(pvlibs)

set(BUILD_FLAGS "-std=c++0x -Wreturn-type -Wno-enum-compare -Wall -O3")

# Include Eigen for matrices
find_package(Eigen REQUIRED)
include_directories(${EIGEN_INCLUDE_DIRS})
add_definitions(${EIGEN_DEFINITIONS})
