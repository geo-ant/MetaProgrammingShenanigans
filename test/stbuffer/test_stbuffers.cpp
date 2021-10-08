//
// Created by georgios on 08.10.21.
//

#include "catch2/catch.hpp"
#include "stbuffer/stbuffer.hpp"
#include <cstdint>

using std::int16_t;
using std::int32_t;

TEST_CASE("buffer of bytes") {
  // the expected results can be verified by hand using e.g.
  // this hex editor https://hexed.it/
  char const buffer[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k'};
  auto [chr, i32, u32] =
      mpsh::copy_from_buffer<char, int32_t, uint16_t>(buffer);
  REQUIRE(chr == 'a');
  REQUIRE(i32 == 1701077858);
  REQUIRE(u32 == 26470);
}

TEST_CASE("buffer of bigger elements") {
  // same buffer as above just with 32bit integers
  int32_t const buffer[] = {1684234849, 1751606885, 7039593};
  auto [chr, i32, u32] =
      mpsh::copy_from_buffer<char, int32_t, uint16_t>(buffer);
  REQUIRE(chr == 'a');
  REQUIRE(i32 == 1701077858);
  REQUIRE(u32 == 26470);
}