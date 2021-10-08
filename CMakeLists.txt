cmake_minimum_required(VERSION 3.20)
project(cppbuffer)
set(CMAKE_CXX_STANDARD 17)


# see here https://docs.conan.io/en/latest/integrations/ide/clion.html
# and here for conan integration for https://github.com/jw3/example-catch2-conan
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

include_directories(include/ ${CONAN_INCLUDE_DIRS_CATCH2})
add_compile_options("-Wall" "-Werror" "-Wextra")

enable_testing()
add_executable(static_buffer_tests test/test_main.cpp test/stbuffer/test_stbuffers.cpp)

add_test(NAME test_static_buffers COMMAND static_buffer_tests)