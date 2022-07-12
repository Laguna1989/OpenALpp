file(GLOB_RECURSE ALLFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)

add_library(OpenALpp_Lib ${ALLFILES})
if (NOT EMSCRIPTEN)
    FetchContent_GetProperties(openal-soft)
    target_link_libraries(OpenALpp_Lib PUBLIC OpenAL)
endif ()

if (MSVC)
    target_compile_options(OpenALpp_Lib PRIVATE "/W3")
    target_compile_options(OpenALpp_Lib PUBLIC "/EHsc")
elseif (EMSCRIPTEN)
    target_compile_options(OpenALpp_Lib PRIVATE "-Wall")
    target_compile_options(OpenALpp_Lib PRIVATE "-Wextra")
    target_compile_options(OpenALpp_Lib PRIVATE "-fpermissive")
else ()
    target_compile_options(OpenALpp_Lib PRIVATE "-Wall")
    target_compile_options(OpenALpp_Lib PRIVATE "-Wextra")
    target_compile_options(OpenALpp_Lib PRIVATE "-fpermissive")
endif ()

target_link_libraries(OpenALpp_Lib PUBLIC libnyquist)
target_include_directories(OpenALpp_Lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../ext/dj_fft)
