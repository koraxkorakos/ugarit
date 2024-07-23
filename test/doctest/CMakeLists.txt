find_package(DocTest REQUIRED)

add_executable(ugarit_doctests)
target_sources(ugarit_doctests 
               PRIVATE  
               main.cpp
               test_meta.cpp)
target_link_libraries(ugarit_doctests ugarit_ doctest::doctest testutils)
gtest_discover_tests(ugarit_doctests)



