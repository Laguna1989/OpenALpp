if (OALPP_ENABLE_INTEGRATION_TESTS)
    add_subdirectory(integration_tests)
endif ()

if (OALPP_ENABLE_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()

if (OALPP_ENABLE_APPROVAL_TESTS)
    add_subdirectory(approval_tests)
endif ()
