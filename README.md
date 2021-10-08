# MetaProgrammingShenanigans

## Introduction
A half-serious repository to collect various meta programming things that don't warrant their own repo.

## Running the Tests
Assuming a working CMake and Conan installation you can run the tests in this repo by cloning it, `cd`ing into the 
directory and executing:

```bash
mkdir build && cd build
conan install ..
cmake .. 
cmake --build .
ctest
```

## Contents
These are the individual projects making up this repository
### stbuffer: Safer Access to Fixed Size Buffers with Static Types
TODO: link blog!