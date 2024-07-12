find_package(GTest REQUIRED)

add_subdirectory(testutils)

add_executable(ugarit_tests)
target_sources(ugarit_tests 
               PRIVATE  
               test_meta.cpp
               test_ugarit.cpp)
target_link_libraries(ugarit_tests ugarit GTest::GTest GTest::Main testutils)
gtest_discover_tests(ugarit_tests)

set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)

