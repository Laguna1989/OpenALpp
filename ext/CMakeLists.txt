if (EMSCRIPTEN)
else ()
    add_subdirectory(openal-soft)
endif ()
add_subdirectory(libnyquist)

if (OALPP_ENABLE_UNIT_TESTS)
    add_subdirectory(catch2)
endif ()
