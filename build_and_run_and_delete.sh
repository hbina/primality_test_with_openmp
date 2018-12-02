#!/usr/bin/env bash
gcc -DNUMBER_OF_THREADS=4 -Wall -O3 -Wpedantic -Wextra -o test.out -fopenmp main.c benchmark_wrapper.c integer_addition_up_to_n.c integer_primality_test.c
./test.out
rm ./test.out