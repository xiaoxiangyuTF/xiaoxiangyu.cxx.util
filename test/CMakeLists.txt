cmake_minimum_required(VERSION 3.0)
project(test_util)

set(MAIN_SOURCE_FILE test_util.cpp)
aux_source_directory(../util/src SRC_DIRS)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -Wall")

# OpenMP
FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message("OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()
include_directories(${OpenMP_INCLUDE_DIRS})

# boost
find_package(Boost REQUIRED)
if(!Boost_FOUND)
    message("Boost NOT FOUND")
endif()
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# opencv
find_package(OpenCV REQUIRED )
if(!Opencv_FOUND)
    message("OpenCV NOT FOUND")
endif()
include_directories(${Opencv_INCLUDE_DIRS})
link_directories(${Opencv_LIBRARY_DIRS})

# include
include_directories (
        /usr/include
        /usr/local/include
)

# source
add_executable(test_util ${MAIN_SOURCE_FILE} ${SRC_DIRS})

# lib
target_link_libraries(test_util
        -pthread
        ${OpenCV_LIBS}
        libboost_regex.so
        libboost_filesystem.so
        libboost_system.so
        libgtest.so
        glog.so
        gtest.so
        libiniparser.so
        )