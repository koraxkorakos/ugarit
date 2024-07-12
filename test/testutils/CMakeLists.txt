add_library(testutils)
target_sources(testutils
               PRIVATE
               src/demangle.cpp)

target_include_directories(testutils
                           PUBLIC 
                           include
                           src) 
