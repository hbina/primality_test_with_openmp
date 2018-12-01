//
// Created by hbina on 01/12/18.
//
#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include "integer_addition_up_to_n.h"


int number_of_threads = 4;

long formula_summation(long integer_n) {
    return integer_n * (integer_n + 1) / 2;
}

long local_integer_summation(long from, long to) {
    long sum = 0;
    for (; from < to; from++) {
        sum += from;
    }
    return sum;
}


/**
 * BEGIN TYPES OF SUMMATION
 */


long serial_summation(long n) {
    long result = 0;
    for (long a = 1; a <= n; a++) {
        result += a;
    }
    return result;
}

void verify_serial_summation() {
    for (long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == serial_summation(integer_n));
    }
    printf("serial summation verification tests passed\n");
}

long parallel_summation_using_critical(long n) {
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

void verify_parallel_summation_using_critical() {
    for (long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == parallel_summation_using_critical(integer_n));
    }
    printf("parallel summation using critical verification tests passed\n");
}

long parallel_summation_using_block(long n) {
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

void verify_parallel_summation_using_block() {
    for (long a = 0; a < test_until_n; a++) {
        long formula_summation = a * (a + 1) / 2;
        assert(formula_summation == parallel_summation_using_critical(a));
    }
    printf("parallel summation using block verification tests passed\n");
}


long parallel_summation_using_promotion_of_scalar(long integer_n) {
    long promoted_total_sum[number_of_threads];
    long local_steps = integer_n / number_of_threads;
    omp_set_num_threads(number_of_threads);
#pragma omp parallel
    {
        long from = local_steps * omp_get_thread_num();
        long to = from + local_steps;

        /**
         * If you are the last guy, you will have to do more work.
         * Could also delegate this to the main thread.
         * Since the main thread will be responsible for merging all of them together.
         * This is done so as to not waste time with context switching
         * But no real way of doing this...
         */
        if (omp_get_thread_num() == (omp_get_num_threads() - 1)) {
            to += integer_n % omp_get_num_threads(); // do the rest of the work
            to += 1; // to include last integer
        }
        promoted_total_sum[omp_get_thread_num()] = local_integer_summation(from, to);
    };
    long actual_total_sum = 0;
    for (int a = 0; a < number_of_threads; a++) {
        actual_total_sum += promoted_total_sum[a];
    }
    return actual_total_sum;
}

void verify_parallel_summation_using_promotion_of_scalar() {
    for (long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == parallel_summation_using_promotion_of_scalar(integer_n));
    }
    printf("parallel summation using promotion of scalar verification tests passed\n");
}

