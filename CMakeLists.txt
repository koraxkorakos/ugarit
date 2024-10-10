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
if (CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_MODULE_COMPILE_FLAGS "-fmodules-ts")
else()
    set(CMAKE_MODULE_COMPILE_FLAGS "")
endif()


# Compile the algorithm header unit
add_custom_command(OUTPUT algorithm.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header algorithm
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the array header unit
add_custom_command(OUTPUT array.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header array
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the iterator header unit
add_custom_command(OUTPUT iterator.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header iterator
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the type_traits header unit
add_custom_command(OUTPUT type_traits.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header type_traits
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the concepts header unit
add_custom_command(OUTPUT concepts.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header concepts
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility header unit
add_custom_command(OUTPUT utility.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header utility
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility ranges unit
add_custom_command(OUTPUT ranges.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header ranges
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility span unit
add_custom_command(OUTPUT span.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header span
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility mdspan unit
add_custom_command(OUTPUT mdspan.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header mdspan
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility cstdint unit
add_custom_command(OUTPUT cstdint.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header cstdint
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility limits unit
add_custom_command(OUTPUT limits.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header limits
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility tuple unit
add_custom_command(OUTPUT tuple.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header tuple
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility numeric unit
add_custom_command(OUTPUT numeric.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header numeric
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Compile the utility string unit
add_custom_command(OUTPUT string.pcm
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++${CMAKE_CXX_STANDARD} ${CMAKE_MODULE_COMPILE_FLAGS} -x c++-system-header string
    DEPENDS ${CMAKE_CXX_COMPILER}
)

# Add the header unit as a dependency
add_custom_target(algorithm_header_unit DEPENDS algorithm.pcm)
add_custom_target(array_header_unit DEPENDS array.pcm)
add_custom_target(atomic_header_unit DEPENDS atomic.pcm)
add_custom_target(concepts_header_unit DEPENDS concepts.pcm)
add_custom_target(cstdint_header_unit DEPENDS cstdint.pcm)
#add_custom_target(iostream_header_unit DEPENDS iostream.pcm)
add_custom_target(iterator_header_unit DEPENDS iterator.pcm)
#add_custom_target(limits_header_unit DEPENDS limits.pcm)
#add_custom_target(limits_header_unit DEPENDS list.pcm)
add_custom_target(mdspan_header_unit DEPENDS mdspan.pcm)
#add_custom_target(mutex_header_unit DEPENDS mutex.pcm)
add_custom_target(numeric_header_unit DEPENDS numeric.pcm)
add_custom_target(optional_header_unit DEPENDS optional.pcm)
#add_custom_target(ranges_header_unit DEPENDS ranges.pcm)
add_custom_target(span_header_unit DEPENDS span.pcm)
add_custom_target(string_header_unit DEPENDS string.pcm)
#add_custom_target(thread_header_unit DEPENDS thread.pcm)
add_custom_target(tuple_header_unit DEPENDS tuple.pcm)
add_custom_target(type_traits_header_unit DEPENDS type_traits.pcm)
#add_custom_target(unordered_set_map_unitDEPENDS unordered_map.pcm)
#add_custom_target(unordered_set_header_unit DEPENDS unordered_set.pcm)
add_custom_target(utility_header_unit DEPENDS utility.pcm)
add_custom_target(variant_header_unit DEPENDS variant.pcm)

add_custom_target(std_headers DEPENDS 
    algorithm_header_unit
    array_header_unit
    concepts_header_unit
    cstdint_header_unit
    iterator_header_unit
    limits_header_unit
    mdspan_header_unit
    numeric_header_unit
    ranges_header_unit
    span_header_unit
    tuple_header_unit
    type_traits_header_unit
    utility_header_unit
    )

# Ensure the header unit is built before the main target

add_library(ugarit STATIC)
#add_dependencies(ugarit std_headers)
target_sources(ugarit
               PUBLIC 
               FILE_SET ugarit_modules TYPE CXX_MODULES               
               FILES src/ugarit.ixx src/core.ixx src/sparse.ixx)
           
target_compile_options(ugarit
               PUBLIC
               $<$<CXX_COMPILER_ID:GNU>:-fmodules-ts>
)

target_include_directories(ugarit
                           SYSTEM
                           PUBLIC
                           include
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
#if (UGARIT_BUILD_THE_MANUAL)
#    add_subdirectory(doc)
#endif()
