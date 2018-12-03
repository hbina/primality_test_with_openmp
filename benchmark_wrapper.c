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
primality_test_benchmark_wrapper(int (*func1)(unsigned long long),
                                 unsigned long long integer_n) {
    double t_begin = omp_get_wtime();
    func1(integer_n);
    double t_diff = omp_get_wtime() - t_begin;
    return t_diff;
}