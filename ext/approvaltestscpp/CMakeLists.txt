message(STATUS "Fetching approvaltests")
include(FetchContent)

FetchContent_Declare(
        approvaltests
        GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp
        GIT_TAG v.10.12.2
)
FetchContent_MakeAvailable(approvaltests)
