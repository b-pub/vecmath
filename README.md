# vecmath
A simple 3D vector math library

## Description

The "vecmath" library is a header-only C++ library for
representing 3D vectors and points, and performing common
calculations with these types.

It is compatible with C++11 through C++20, but by default
the tests build with C++11.

## Building

You'll need CMake 3.10 or newer to build vecmath tests.

To build the vecmath tests, clone this repo and the sibling
"btest" repo. On Linux, MacOS, and MinGW or WSL environments on
Windows, build and run with these commands:

    $ mkdir hacking && cd hacking
    $ git clone https://github.com/b-pub/vecmath.git
    $ git clone https://github.com/b-pub/btest.git
    $ cd vecmath
    $ mkdir build && cd build
    $ cmake ..
    $ make -j
    $ ./runtests

This should prepare and run the build, resulting in the final
executable, runtests. The last few lines of runtests' output will
show the number of tests, number of failed tests, and number of
passed tests.

## Usage

Your project can use the vecmath library by simple inclusion
of the `<vecmath.h>` header. This header defines the `vecmath::`
namespace, which contains the `Vector3<>` and `Point3<>`
class templates.

Convenience types of `Vector3f`, `Vector3d`, `Point3f`, and `Point3d`
are provided for cleaner references to `<float>` and `<double>`
specializations.

Documentation beyond the `vecmath.h` header will be available
eventually.

## Author

The vecmath library was written by Brent Burton.  It was
originally written in 1996 in C, went through several additions
and changes between 1997-2008, and was rewritten in modern C++ in
2022.

Copyright 1996-2022 Brent Burton

Licensed under the MIT License. See LICENSE for details.
