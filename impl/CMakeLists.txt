FetchContent_GetProperties(openal-soft)

file(GLOB ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_executable(OpenALTryout ${ALLFILES})
target_link_libraries(OpenALTryout OpenAL)
target_include_directories(OpenALTryout PUBLIC ${CMAKE_SOURCE_DIR}/ext/stb_vorbis)
