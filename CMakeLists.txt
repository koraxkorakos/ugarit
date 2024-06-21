cmake_minimum_required(VERSION 3.7.0...3.28.99)
project(ugarit_project
        VERSION 0.0.0.1
        DESCRIPTION "Universal Geometric Algebra Library for C++"
        HOMEPAGE_URL https://github.com/koraxkorakos/ugarit
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
# not fully supported by our cmake

#find_package(Boost, REQUIRED program_options system filesystem exception)
#find_package(Eigen3 REQUIRED NO_MODULE)

include(ExternalProject)
ExternalProject_Add(googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           main
    SOURCE_DIR        "${CMAKE_BINARY_DIR}/googletest-src"
    BINARY_DIR        "${CMAKE_BINARY_DIR}/googletest-build"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include"
)
endif()


add_library(ugarit)

target_sources(ugarit
               PRIVATE
               src/ugarit.cpp)

target_include_directories(ugarit
                           PUBLIC 
                           $<INSTALL_INTERFACE:include>    
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src)
               
set_property(TARGET ugarit
             PROPERTY PUBLIC_HEADER
             include/ugarit/ugarit.hpp)                           

target_link_libraries(ugarit
                      PUBLIC)

install(TARGETS ugarit
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

option(BUILD_TESTS "Build unit tests" On)        
if(${BUILD_TESTS})
  enable_testing()

  add_library(testutils)

  target_sources(testutils
                 PRIVATE
                 src/demangle.cpp)

  target_include_directories(testutils
                             PUBLIC 
                             $<INSTALL_INTERFACE:include>    
                             $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                             PRIVATE
                             ${CMAKE_CURRENT_SOURCE_DIR}/src)

   set_property(TARGET testutils 
                PROPERTY PUBLIC_HEADER
                include/testutils/demangle.hpp)

   add_subdirectory("test")
endif()