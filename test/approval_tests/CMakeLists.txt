file(GLOB TESTFILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*)
add_executable(OpenALpp_ApprovalTests ${TESTFILES})

target_link_libraries(OpenALpp_ApprovalTests PRIVATE
        OpenALpp_Lib
        ApprovalTests::ApprovalTests
        Catch2::Catch2WithMain)

if (NOT OALPP_STATIC_LIBRARY)
    message(WARNING "Building OpenALpp unit tests with dynamic library: dll/so will not be copied by default.")
endif ()

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_link_options(OpenALpp_ApprovalTests PRIVATE --preload-file assets)
    target_link_options(OpenALpp_ApprovalTests PRIVATE "SHELL:-s TOTAL_MEMORY=256MB")
    target_link_options(OpenALpp_ApprovalTests PRIVATE "SHELL:-s ALLOW_MEMORY_GROWTH=1")
endif ()

add_test(NAME OpenALpp_ApprovalTests COMMAND OpenALpp_ApprovalTests)

use_assets(OpenALpp_ApprovalTests)
