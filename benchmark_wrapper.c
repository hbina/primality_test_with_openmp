//
// Created by hbina on 01/12/18.
//

#include <omp.h>

double addition_benchmark_wrapper(unsigned long long (*func)(unsigned long long), unsigned long long integer_n) {
    double t_begin = omp_get_wtime();
    func(integer_n);
    double t_diff = omp_get_wtime() - t_begin;
    return t_diff;
}

double
primality_test_benchmark_wrapper(char (*func1)(unsigned long long),
                                 unsigned long long *primes_example,
                                 int how_many) {
    double t_begin = omp_get_wtime();
    for (int prime_example_index = 1; prime_example_index < how_many; prime_example_index++) {
        func1(primes_example[prime_example_index]);
    }
    double t_diff = omp_get_wtime() - t_begin;
    return t_diff;
}