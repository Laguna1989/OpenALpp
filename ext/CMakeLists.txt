add_subdirectory(openal-soft)
add_subdirectory(libnyquist)

if (OALPP_ENABLE_UNIT_TESTS)
    add_subdirectory(catch2)
endif ()
