cmake_minimum_required(VERSION 3.12)
project(lab_words)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -stdlib=libc++")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.69.0 REQUIRED COMPONENTS filesystem locale system)
find_package(LibArchive)
include_directories(.)
INCLUDE_DIRECTORIES(${LibArchive_INCLUDE_DIR})

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(lab_words main.cpp conf_read.cpp conf_read.h unzip.cpp unzip.h)
    target_link_libraries(lab_words ${Boost_LIBRARIES})
endif()

target_link_libraries(lab_words ${LibArchive_LIBRARIES})
