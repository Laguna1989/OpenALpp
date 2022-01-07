file(GLOB ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(OpenALPP_Lib ${ALLFILES})
if (EMSCRIPTEN)
elseif ()
    FetchContent_GetProperties(openal-soft)
    target_link_libraries(OpenALPP_Lib OpenAL)
endif ()

target_link_libraries(OpenALPP_Lib libnyquist)
target_include_directories(OpenALPP_Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})


