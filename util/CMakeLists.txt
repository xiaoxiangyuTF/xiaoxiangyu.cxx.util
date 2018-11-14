cmake_minimum_required(VERSION 3.0)
project(xiaoxiangyuTF.cxx.util)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -Wall")

# boost
find_package(Boost REQUIRED)
if(!Boost_FOUND)
    message("Boost NOT FOUND")
endif()
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# include
include_directories (
        /usr/include
        /usr/local/include
)

# add source directory
aux_source_directory(src SRC_DIRS)

# generate lib
add_library(xiaoxiangyuTF.cxx.util ${SRC_DIRS})

# add lib
target_link_libraries(xiaoxiangyuTF.cxx.util
        libboost_regex.so
        libboost_filesystem.so
        libboost_system.so
        libgtest.so
        glog.so
        gtest.so
        libiniparser.so
        )