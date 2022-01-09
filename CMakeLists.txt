cmake_minimum_required(VERSION 3.19)
project(OpenAlTryout)

option(OALPP_ENABLE_UNIT_TESTS "Enable unit tests" ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /EHsc")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O0 -g --std=c++17 -fpermissive")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  --preload-file assets")
    add_link_options("SHELL:-s TOTAL_MEMORY=256MB " "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD 17)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
add_subdirectory(ext)
add_subdirectory(impl)
add_subdirectory(test)

## copy .clang-format to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)
