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
Let's say we have fixed size array of 8 bytes, and we want to read the first two bytes as a `int16_t`, the next four bytes a an `int32_t` and the next two bytes as `uint16_t`. 
This project allows us to do this with an intuitive API in C++17. It will even complain
_at compile time_ when too many elements are read from the buffer.

```c++
uint8_t buf[] = /* an array with compile-time known size*/
auto [i16, i32, u16] = copy_from_buffer<int16_t,uint32_t,uint16_t>(buf);
```
Check out [this blog article](https://geo-ant.github.io/blog/2021/statically-typed-reading-from-fixed-size-buffer/) for more 
information.