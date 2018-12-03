//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_BENCHMARK_WRAPPER_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_BENCHMARK_WRAPPER_H

double addition_benchmark_wrapper(unsigned long long (*func)(unsigned long long), unsigned long long);

double primality_test_benchmark_wrapper(char (*)(unsigned long long), unsigned long long);

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_BENCHMARK_WRAPPER_H
