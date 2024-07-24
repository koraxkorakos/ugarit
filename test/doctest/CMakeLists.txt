find_package(doctest REQUIRED)

include("${CMAKE_BINARY_DIR}/_deps/doctest-src/scripts/cmake/doctest.cmake")

message("BUILD doctests")
add_executable(ugarit_doctests)
target_sources(ugarit_doctests 
               PRIVATE  
               main.cpp
               test_meta.cpp)
target_link_libraries(ugarit_doctests ugarit doctest::doctest ugarit_testutils)
doctest_discover_tests(ugarit_doctests)



