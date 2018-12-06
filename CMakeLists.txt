cmake_minimum_required(VERSION 3.10)
project(performance_of_prime_primality C)

add_definitions(-DNUMBER_OF_THREADS=4)
add_definitions(-DENABLE_UNIT_TEST=1)
add_definitions(-DENABLE_BENCMARK=1)
add_definitions(-DENABLE_VERBOSE=1)

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(performance_of_prime_primality main.c integer_addition_up_to_n.h benchmark_wrapper.h integer_addition_up_to_n.c benchmark_wrapper.c primality_test.c primality_test.h)
