message(STATUS "Fetching openal-soft")
include(FetchContent)

set(ALSOFT_UTILS OFF CACHE BOOL "")
set(ALSOFT_EXAMPLES OFF CACHE BOOL "")
set(ALSOFT_UPDATE_BUILD_VERSION OFF CACHE BOOL "")

FetchContent_Declare(
        openal-soft
        GIT_REPOSITORY https://github.com/kcat/openal-soft
        GIT_TAG 1.21.1
)

FetchContent_MakeAvailable(openal-soft)
