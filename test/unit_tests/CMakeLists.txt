message(STATUS "Fetching catch2")


file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(OpenALPP_UnitTests ${TESTFILES})
target_link_libraries(OpenALPP_UnitTests PRIVATE
        OpenALPP_Lib
        Catch2::Catch2)

FetchContent_GetProperties(catch2)
target_include_directories(OpenALPP_UnitTests PUBLIC ${catch2_SOURCE_DIR}/include)
