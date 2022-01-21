file(GLOB_RECURSE ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(OpenALpp_Lib ${ALLFILES})
if (EMSCRIPTEN)
    target_link_options(OpenALpp_Lib PUBLIC -lopenal)
else ()
    FetchContent_GetProperties(openal-soft)
    target_link_libraries(OpenALpp_Lib PUBLIC OpenAL)
endif ()

target_link_libraries(OpenALpp_Lib PUBLIC libnyquist)
target_include_directories(OpenALpp_Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
