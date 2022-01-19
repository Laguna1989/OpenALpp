cmake_minimum_required(VERSION 3.19)
project(OpenALpp)

option(OALPP_ENABLE_UNIT_TESTS "Enable unit tests" ON)
option(OALPP_ENABLE_INTEGRATION_TESTS "Enable integration tests" ON)
option(OALPP_STATIC_LIBRARY "Build openal as static library" OFF)

if (OALPP_STATIC_LIBRARY)
    set(LIBTYPE STATIC)
endif ()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /EHsc")
elseif (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -g -fpermissive")
    add_link_options("SHELL:-s TOTAL_MEMORY=256MB " "SHELL:-s ALLOW_MEMORY_GROWTH=1")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2 -g -fpermissive")
endif ()

#if (NOT EMSCRIPTEN)
#    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD 14)

# speed up fetchcontent on consecutive runs
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
add_subdirectory(ext)
add_subdirectory(impl)
add_subdirectory(test)

## copy .clang-format to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)
