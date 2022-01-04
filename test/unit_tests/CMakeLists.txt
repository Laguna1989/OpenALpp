message(STATUS "Fetching catch2")
include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v2.13.8
)
FetchContent_MakeAvailable(Catch2)


file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(OpenALPP_UnitTests ${TESTFILES})
target_link_libraries(OpenALPP_UnitTests PRIVATE
        OpenALPP_Lib
        Catch2::Catch2)
