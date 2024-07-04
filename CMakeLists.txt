cmake_policy(SET CMP0048 NEW) 
cmake_minimum_required(VERSION 3.30...3.30)
project(ugarit_project
        VERSION 0.0.0.1
        DESCRIPTION "Universal Geometric Algebra Library for C++"
        HOMEPAGE_URL https://github.com/koraxkorakos/ugarit
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)     
set(CMAKE_CXX_EXTENSIONS Off)

option(UGARIT_IMPORT_STD_MODULE "Enable import std" Off)

if (UGARIT_IMPORT_STD_MODULE)
   set(CMAKE_CXX_STANDARD 23)   
   set(CMAKE_CXX_MODULE_STD On)   
endif()

set(CXX_SCAN_FOR_MODULES On)    

# The following "import std" C++23 features is not implemented in most recent GCC and CLANG
#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
#set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP On)

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


add_library(ugarit STATIC)

target_compile_features(ugarit
    PRIVATE   cxx_std_20
    INTERFACE cxx_std_20
)

target_compile_options(ugarit
    PUBLIC
     $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>
)

target_sources(ugarit
               PUBLIC
               FILE_SET ugarit TYPE CXX_MODULES FILES
               src/ugarit.cpp)

target_link_libraries(ugarit
                      PRIVATE)

# Make an executable.
add_executable(main)
# Note that this source is *not* allowed to `import std` as it ends up
# with only C++20 support due to the `uses_std` INTERFACE requirements.
target_sources(main
  PRIVATE src/main.cpp)
target_link_libraries(main PRIVATE ugarit)


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