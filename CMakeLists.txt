cmake_minimum_required(VERSION 3.0)
project(demo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -Wall")

# source
set(MAIN_SOURCE_FILE main.cpp)

# include
include_directories (
        /usr/include
        /usr/local/include
)

# add source directory
aux_source_directory(util/src DIR_SRCS)

# add subdirectory
add_subdirectory(util)

# source
add_executable(demo ${MAIN_SOURCE_FILE})

# lib
target_link_libraries(demo
        xiaoxiangyuTF.cxx.util
        )