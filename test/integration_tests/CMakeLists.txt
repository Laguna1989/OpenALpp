file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(OpenALpp_Integration ${TESTFILES})

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(OpenALpp_Integration PUBLIC --preload-file assets)
    target_link_options(OpenALpp_Integration PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(OpenALpp_Integration PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()
target_link_libraries(OpenALpp_Integration OpenALpp_Lib)

if (NOT OALPP_STATIC_LIBRARY)
    message(WARNING "Building OpenALpp integration tests with dynamic library: dll/so will not be copied by default.")
endif ()

use_assets(OpenALpp_Integration)
