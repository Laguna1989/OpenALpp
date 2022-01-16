if (OALPP_ENABLE_INTEGRATION_TESTS)
    add_subdirectory(integration)
endif ()

if (OALPP_ENABLE_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()
