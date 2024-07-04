find_package(GTest REQUIRED)

add_executable(ugarit_tests)

target_sources(ugarit_tests 
               PRIVATE  
               test_ugarit.cpp
               test_meta.cpp)

#target_link_libraries(ugarit_tests ugarit GTest::Main testutils)
target_link_libraries(ugarit_tests ugarit GTest::Main testutils)

gtest_discover_tests(ugarit_tests)

set_tests_properties(${noArgsTests}   PROPERTIES TIMEOUT 10)

