cmake_minimum_required(VERSION 3.2)
project(CIRCULAR_BUFFER CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(header_files ${PROJECT_SOURCE_DIR}/include/CircularBuffer.hpp)

add_library(circular_buffer INTERFACE)

target_sources(circular_buffer INTERFACE $<BUILD_INTERFACE:${detail_header_files} ${header_files}>)
target_include_directories(circular_buffer INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)
target_include_directories(circular_buffer SYSTEM INTERFACE $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>)

add_executable(test_circular_buffer ${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp)
target_link_libraries(test_circular_buffer circular_buffer)
