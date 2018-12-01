#!/usr/bin/env bash
gcc -Wall -Wverbose -o test.out -fopenmp main.c benchmark_wrapper.c integer_addition_up_to_n.c
./test.out
rm ./test_out