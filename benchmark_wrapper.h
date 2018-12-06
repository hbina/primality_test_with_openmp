//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_BENCHMARK_WRAPPER_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_BENCHMARK_WRAPPER_H

typedef struct {
    double serial_summation;
    double parallel_summation_using_promotion_of_scalar;
    double parallel_summation_using_atomic;
    double parallel_summation_using_critical;

    double serial_primality_test;
    double parallel_primality_test_using_promotion_of_scalar;
    double parallel_primality_test_using_sentinel;
} primality_statistics;


double addition_benchmark_wrapper(unsigned long long (*func)(unsigned long long), unsigned long long);

double primality_test_benchmark_wrapper(int (*)(unsigned long long), unsigned long long);

void benchmark_primality_test(unsigned long long *, int);

void benchmark_find_all_primes(unsigned long long, int (*)(unsigned long long));

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_BENCHMARK_WRAPPER_H
