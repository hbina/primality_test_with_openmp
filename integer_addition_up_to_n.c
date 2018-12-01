//
// Created by hbina on 01/12/18.
//
#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include "integer_addition_up_to_n.h"


int number_of_threads = 4;

void begin_test_integer_summation() {
    integer_summation(test_until_n);
}

long integer_summation(long n) {
    long total_sum = 0;
    long local_steps = n / number_of_threads;
#pragma omp parallel
    {
        long from = local_steps * omp_get_thread_num();
        long to = from + local_steps;

        if (omp_get_thread_num() == (omp_get_num_threads() - 1)) {
            to += n % omp_get_num_threads();
            to += 1;
        }
        long local_sum = local_integer_summation(from, to);
#pragma omp critical
        total_sum += local_sum;
    };
    return total_sum;
}

long local_integer_summation(long from, long to) {
    long sum = 0;
    for (; from < to; from++) {
        sum += from;
    }
    return sum;
}


/**
 * UNIT TEST
 */
void verify_summation_of_n() {
    for (int a = 0; a < test_until_n; a++) {
        long formula_summation = a * (a + 1) / 2;
        assert(formula_summation == integer_summation(a));
    }
    printf("all verification tests passed\n");
}

long serial_summation(long n) {
    long result = 0;
    for (long a = 1; a <= n; a++) {
        result += a;
    }
    return result;
}
