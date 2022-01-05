message(STATUS "Fetching libnyquist")
include(FetchContent)

FetchContent_Declare(
        libnyquist
        GIT_REPOSITORY https://github.com/ddiakopoulos/libnyquist
        GIT_TAG master
)
FetchContent_MakeAvailable(libnyquist)
