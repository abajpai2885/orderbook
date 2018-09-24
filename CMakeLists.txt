cmake_minimum_required(VERSION 3.4)
project(jt-orderbook)

set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CXX_FLAGS
        -std=c++14
        )

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

include_directories(${PROJECT_SOURCE_DIR})
message("project path:" ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
        main.cpp
        main.cpp engine.cpp feed_handler.cpp)

add_executable(matchengine ${SOURCE_FILES})
#add_executable(perf_score ${SOURCE_FILES})
#set_target_properties(
#        perf_score
#        PROPERTIES
#        COMPILE_DEFINITIONS PROFILE=1)
