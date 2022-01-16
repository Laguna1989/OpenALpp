message(STATUS "Fetching libnyquist")
include(FetchContent)

set(BUILD_EXAMPLE OFF CACHE BOOL "")

FetchContent_Declare(
        libnyquist
        GIT_REPOSITORY https://github.com/ddiakopoulos/libnyquist
        GIT_TAG master
)
FetchContent_MakeAvailable(libnyquist)
