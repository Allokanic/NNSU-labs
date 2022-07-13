cmake_minimum_required(VERSION 3.12)

set(ProjectId animated_matrix)

project(${ProjectId})

#add_library(${ProjectId} STATIC ${ALL_SOURCE_FILES})
add_executable (${ProjectId} main.cpp rational.h rational.cpp menu.h menu.cpp matrix.cpp matrix.h)