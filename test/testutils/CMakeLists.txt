add_library(ugarit_testutils)
target_sources(ugarit_testutils
               PRIVATE
               src/demangle.cpp)

target_include_directories(ugarit_testutils
                           PUBLIC 
                           include
                           src) 