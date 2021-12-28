message(STATUS "Fetching openal-soft")
include(FetchContent)

FetchContent_Declare(
        openal-soft
        GIT_REPOSITORY https://github.com/kcat/openal-soft
        GIT_TAG 1.21.1
)
FetchContent_MakeAvailable(openal-soft)
