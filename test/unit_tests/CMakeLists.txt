message(STATUS "Fetching catch2")

file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(OpenALpp_UnitTests ${TESTFILES})
target_link_libraries(OpenALpp_UnitTests PRIVATE
        OpenALpp_Lib
        Catch2::Catch2WithMain)

FetchContent_GetProperties(catch2)
target_include_directories(OpenALpp_UnitTests PUBLIC ${catch2_SOURCE_DIR}/include)

if (NOT OALPP_STATIC_LIBRARY)
    message(WARNING "Building OpenALpp unit tests with dynamic library: dll/so will not be copied by default.")
endif ()

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(OpenALpp_UnitTests PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(OpenALpp_UnitTests PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()
