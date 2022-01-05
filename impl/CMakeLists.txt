FetchContent_GetProperties(openal-soft)

file(GLOB ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(OpenALPP_Lib ${ALLFILES})
target_link_libraries(OpenALPP_Lib OpenAL libnyquist)
target_include_directories(OpenALPP_Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR})
