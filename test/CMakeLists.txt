add_subdirectory(testutils)

if(${UGARIT_GTESTS})
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(gtest)
    message("building doctests")
endif()

if(${UGARIT_DOCTESTS})
    FetchContent_MakeAvailable(doctest)
    add_subdirectory(doctest)
    message("building google tests")
endif()

set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 20)

