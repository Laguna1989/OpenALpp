add_subdirectory(openal-soft)

if (OALPP_ENABLE_UNIT_TESTS)
    add_subdirectory(catch2)
endif ()
