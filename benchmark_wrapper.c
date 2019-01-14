//
// Created by hbina on 01/12/18.
//

#include <omp.h>
#include <stdio.h>
#include "benchmark_wrapper.h"
#include "primality_test.h"

double addition_benchmark_wrapper(unsigned long long (*func)(unsigned long long), unsigned long long integer_n) {
    double t_begin = omp_get_wtime();
    func(integer_n);
    double t_diff = omp_get_wtime() - t_begin;
    return t_diff;
}

double
primality_test_benchmark_wrapper(int (*function_to_benchmark)(unsigned long long),
                                 unsigned long long integer_n) {
    double t_begin = omp_get_wtime();
    function_to_benchmark(integer_n);
    double t_diff = omp_get_wtime() - t_begin;
    return t_diff;
}

void benchmark_primality_test(unsigned long long *examples, int number_of_prime_examples) {
    primality_statistics primality_stats = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    for (int a = 0; a < number_of_prime_examples; a++) {
        primality_stats.serial_primality_test += primality_test_benchmark_wrapper(
                &serial_primality_test,
                examples[a]);
        primality_stats.parallel_primality_test_using_promotion_of_scalar +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_basic,
                        examples[a]);

        primality_stats.parallel_primality_test_using_sentinel +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_sentinel,
                        examples[a]);
    }
    printf("serial_primality_test:\n%e\n", primality_stats.serial_primality_test / number_of_prime_examples);
    printf("parallel_primality_test_basic:\n%e\n",
           primality_stats.parallel_primality_test_using_promotion_of_scalar / number_of_prime_examples);
    printf("parallel_primality_test_sentinel:\n%e\n",
           primality_stats.parallel_primality_test_using_sentinel / number_of_prime_examples);
}

void benchmark_find_all_primes(unsigned long long integer_n, int (*func)(unsigned long long)) {
    UllArray ullArray;
    double t_begin = omp_get_wtime();
    find_all_primes(integer_n, func, &ullArray);
    double t_diff = omp_get_wtime() - t_begin;
    printf("it took %e seconds to find all the primes between 3 and %llu\n", t_diff, integer_n);
}
