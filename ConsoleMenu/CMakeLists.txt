cmake_minimum_required(VERSION 3.12)

set(ProjectId menu)

project(${ProjectId})

#add_library(${ProjectId} STATIC ${ALL_SOURCE_FILES})
add_executable (${ProjectId} menu.h menu.cpp)