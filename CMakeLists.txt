cmake_minimum_required(VERSION 3.30...3.30.20240621-gb83fabd)
if (UGARIT_IMPORT_STD_MODULE)
    # Set experimental flag to enable `import std` support from CMake.
    # This must be enabled before C++ language support.
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
    # This specific value changes as experimental support evolves. See
    # `Help/dev/experimental.rst` in the CMake source corresponding to
    # your CMake build for the exact value to use.
    "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP On)  
  set(CMAKE_CXX_MODULE_STD On)
endif()

project(ugarit_project
        VERSION 0.0.0.1
        DESCRIPTION "Universal Geometric Algebra Library for C++"
        HOMEPAGE_URL https://github.com/koraxkorakos/ugarit
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)     
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_CXX_SCAN_FOR_MODULES On)
# -----------------------------------------------------------------------------
option(UGARIT_IMPORT_STD_MODULE "Enable import std" Off)
option(UGARIT_DOCTESTS "Build doctest unit tests" On)
option(UGARIT_GTESTS "Build googletest unit tests" On)
option(UGARIT_DOXYDOC "Build source documentation" Off)
option(UGARIT_BUILD_THE_MANUAL "Build the manual" On)

#find_package(Boost, REQUIRED program_options system filesystem exception)
#find_package(Eigen3 REQUIRED NO_MODULE)

if(${UGARIT_DOCTESTS})
    set (UGARIT_UNITTESTS On)
elseif(${ugarit_GTESTS})
    set (UGARIT_UNITTESTS On)
else()
    set (UGARIT_UNITTESTS Off)
endif()

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        main
)

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG        master
)

if(${UGARIT_GTESTS})
    FetchContent_MakeAvailable(googletest)
endif()

if(${UGARIT_DOCTESTS})
    FetchContent_MakeAvailable(doctest)
endif()

# -----------------------------------------------------------------------------
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library(ugarit STATIC)
target_sources(ugarit
               PUBLIC 
               FILE_SET ugarit_modules TYPE CXX_MODULES               
               FILES src/meta.ixx src/ugarit.ixx src/core.ixx)
           
target_compile_options(ugarit
               PUBLIC
               $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>
)

target_include_directories(ugarit
                           PUBLIC
                           include
)

target_link_libraries(ugarit
                      PRIVATE
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
add_executable(ugarit_main src/main.cpp)
target_link_libraries(ugarit_main  ugarit)              

if (${UGARIT_UNITTESTS})     
    enable_testing()
    add_subdirectory(test)
    message("Building unit tests")
endif()

# -----------------------------------------------------------------------------
if(${UGARIT_DOXYDOC})
    find_package(Doxygen
                 REQUIRED dot
                 OPTIONAL_COMPONENTS mscgen dia)

    doxygen_add_docs(ugaritdox)
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
if (UGARIT_BUILD_THE_MANUAL)
    add_subdirectory(doc)
endif()
