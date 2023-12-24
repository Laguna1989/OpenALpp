cmake_minimum_required(VERSION 3.19)
project(OpenALpp VERSION 0.1.0 LANGUAGES CXX)

option(OALPP_ENABLE_UNIT_TESTS "Enable unit tests" ON)
option(OALPP_ENABLE_APPROVAL_TESTS "Enable approval tests" ON)
option(OALPP_ENABLE_INTEGRATION_TESTS "Enable integration tests" ON)
option(OALPP_STATIC_LIBRARY "Build openal as static library" ON)

if (OALPP_STATIC_LIBRARY)
    set(LIBTYPE STATIC)
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD 20)

# speed up fetchcontent on consecutive runs
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
add_subdirectory(ext)
add_subdirectory(impl)
add_subdirectory(test)

## copy .clang-format to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)
