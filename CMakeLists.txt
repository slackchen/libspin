cmake_minimum_required(VERSION 3.7)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

set(Boost_INCLUDE_DIR /Users/adrian/Downloads/boost_1_64_0)
set(Boost_LIBRARY_DIR /Users/adrian/Downloads/boost_1_64_0/stage/lib)

set(Boost_USE_STATIC_LIBS        ON) # only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS system thread date_time regex serialization REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(libspin)
include_directories(libspin)

set(SOURCE_FILES main.cpp Headers.h)
add_executable(untitled ${SOURCE_FILES})
if(Boost_FOUND)
    target_link_libraries(untitled ${Boost_LIBRARIES} spin)
endif()

add_executable(AsioTest Tests/AsioTest.cpp)
if(Boost_FOUND)
    target_link_libraries(AsioTest ${Boost_LIBRARIES} spin)
endif()

add_executable(MaybeTest Tests/MaybeTest.cpp)
target_link_libraries(MaybeTest spin)
add_executable(ChannelTest Tests/ChannelTest.cpp)
target_link_libraries(ChannelTest spin)
add_executable(PromiseTest Tests/PromiseTest.cpp)
target_link_libraries(PromiseTest spin)



