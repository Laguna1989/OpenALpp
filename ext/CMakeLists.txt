# begin-snippet: cpm_download
message(STATUS "Add CPM.cmake")
# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)
# end-snippet

message(STATUS "Fetching external libraries started")


if (NOT EMSCRIPTEN)
    message(STATUS "Fetching openal-soft")
    CPMAddPackage(
            NAME openal-soft
            GITHUB_REPOSITORY kcat/openal-soft
            GIT_TAG 1.21.1
            OPTIONS
            "ALSOFT_UTILS OFF"
            "ALSOFT_EXAMPLES OFF"
            "ALSOFT_UPDATE_BUILD_VERSION OFF"
    )
endif ()

message(STATUS "Fetching libnyquist")
CPMAddPackage(
        NAME libnyquist
        GITHUB_REPOSITORY ddiakopoulos/libnyquist
        GIT_TAG master
        OPTIONS
        "LIBNYQUIST_BUILD_EXAMPLE OFF"
)

if (OALPP_ENABLE_UNIT_TESTS)
    message(STATUS "Fetching catch2")
    CPMAddPackage(
            NAME catch2
            GITHUB_REPOSITORY catchorg/Catch2
            GIT_TAG v3.5.0
    )
endif ()


if (OALPP_ENABLE_APPROVAL_TESTS)
    # begin-snippet: cpm_add_approvaltests
    message(STATUS "Fetching approvaltests")
    CPMAddPackage(
            NAME approvaltests
            GITHUB_REPOSITORY approvals/ApprovalTests.cpp
            GIT_TAG master
    )
    # end-snippet
endif ()
