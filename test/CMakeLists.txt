add_subdirectory(testutils)

if(${CSB_GTESTS})
    FetchContent_MakeAvailable(googletest)
endif()

if(${CSB_DOCTESTS})
    FetchContent_MakeAvailable(doctest)
endif()

set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 20)

