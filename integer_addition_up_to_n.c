//
// Created by hbina on 01/12/18.
//
#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include "integer_addition_up_to_n.h"

unsigned long long formula_summation(unsigned long long integer_n) {
    return integer_n * (integer_n + 1) / 2;
}

unsigned long long local_integer_summation(unsigned long long from, unsigned long long to) {
    unsigned long long sum = 0l;
    for (; from < to; from++) {
        sum += from;
    }
    return sum;
}


/**
 * BEGIN TYPES OF SUMMATION
 */


unsigned long long serial_summation(unsigned long long integer_n) {
    unsigned long long result = 0;
    for (unsigned long long a = 1; a <= integer_n; a++) {
        result += a;
    }
    return result;
}

void verify_serial_summation(unsigned long long test_until_n) {
    for (unsigned long long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == serial_summation(integer_n));
    }
    printf("serial summation verification tests passed\n");
}

unsigned long long parallel_summation_using_atomic(unsigned long long integer_n) {
    unsigned long long total_sum = 0l;
    unsigned long long local_steps = integer_n / omp_get_max_threads();
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_max_threads();
        unsigned long long from = local_steps * thread_id;
        unsigned long long to = from + local_steps;

        /**
         * The last thread will have to do more work because some integer_n will not be divisible by NUMBER_OF_THREADS
         */
        if (thread_id == (thread_count - 1)) {
            unsigned long long remainder = (integer_n % (unsigned long long) thread_count) + 1;
            to += remainder;
        }
        unsigned long long local_sum = local_integer_summation(from, to);
#pragma omp atomic update
        total_sum += local_sum;
    };
    return total_sum;
}

void verify_parallel_summation_using_atomic(unsigned long long test_until_n) {
    for (unsigned long long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == parallel_summation_using_atomic(integer_n));
    }
    printf("parallel summation using atomic verification tests passed\n");
}

unsigned long long parallel_summation_using_critical(unsigned long long integer_n) {
    unsigned long long total_sum = 0;
    unsigned long long local_steps = integer_n / omp_get_max_threads();
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_max_threads();
        unsigned long long from = local_steps * thread_id;
        unsigned long long to = from + local_steps;

        /**
         * The last thread will have to do more work because some integer_n will not be divisible by NUMBER_OF_THREADS
         */
        if (thread_id == (thread_count - 1)) {
            to += integer_n % thread_count;
            to += 1;
        }
        unsigned long long local_sum = local_integer_summation(from, to);
#pragma omp critical
        total_sum += local_sum;
    };
    return total_sum;
}

void verify_parallel_summation_using_critical(unsigned long long test_until_n) {
    for (unsigned long long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == parallel_summation_using_critical(integer_n));
    }
    printf("parallel summation using critical verification tests passed\n");
}


unsigned long long parallel_summation_using_promotion_of_scalar(unsigned long long integer_n) {
    unsigned long long promoted_total_sum[4] = {0};
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        promoted_total_sum[thread_id] = 0l;
        for (unsigned long long local_begin = (unsigned long long) thread_id;
             local_begin <= integer_n; local_begin += 4l) {
            promoted_total_sum[thread_id] += local_begin;
        }
    };
    unsigned long long actual_total_sum = 0;
    for (int a = 0; a < omp_get_max_threads(); a++) {
        actual_total_sum += promoted_total_sum[a];
    }
    return actual_total_sum;
}

void verify_parallel_summation_using_promotion_of_scalar(unsigned long long test_until_n) {
    for (unsigned long long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == parallel_summation_using_promotion_of_scalar(integer_n));
    }
    printf("parallel summation using promotion of scalar verification tests passed\n");
}

