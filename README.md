# ugarit
Universal Geoetric Algebra library for C++.


TOOLS
=====

Due to use of C++ modules you need to choose "Ninja" as the generator. Note, that you compiler needs to support  C++20 named modules too. You need a compiler that supports C++20 modules.
At the time of writing only recent MSVC and Clang provide the necessary support. GCC 14 has incomplete support for C++20 modules and is not fully supported by CMake. For minimal  CMake version requirements see the root CMakeLists.txt. Experimental support for C++ modules is present from CMake 3.28.3 on, but CMake 3.30 has more complete and stable  support.

C++23 import of std module is not yet supported. because cmake support for that is still experimental.
=======
# ugarit 𐎁𐎘𐎐𐎚𐎋 

Universal Geometric Algebra library for C++.

## Library Name
Ugarit as an acronym stands for "Universal Geometric Algebra Rewritten in Templates"

## Requirements
Needs a C++ 20 compliant compiler.
