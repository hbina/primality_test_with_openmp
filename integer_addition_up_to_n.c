//
// Created by hbina on 01/12/18.
//
#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include "integer_addition_up_to_n.h"

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


long serial_summation(long integer_n) {
    long result = 0;
    for (long a = 1; a <= integer_n; a++) {
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

long parallel_summation_using_atomic(long integer_n) {
    long total_sum = 0;
    long local_steps = integer_n / NUMBER_OF_THREADS;
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
        long from = local_steps * thread_id;
        long to = from + local_steps;

        /**
         * The last thread will have to do more work because some integer_n will not be divisible by NUMBER_OF_THREADS
         */
        if (thread_id == (thread_count - 1)) {
            to += integer_n % thread_count;
            to += 1;
        }
        long local_sum = local_integer_summation(from, to);
#pragma omp atomic
        total_sum += local_sum;
    };
    return total_sum;
}

void verify_parallel_summation_using_atomic() {
    for (long integer_n = 0; integer_n < test_until_n; integer_n++) {
        assert(formula_summation(integer_n) == parallel_summation_using_atomic(integer_n));
    }
    printf("parallel summation using atomic verification tests passed\n");
}

long parallel_summation_using_critical(long integer_n) {
    long total_sum = 0;
    long local_steps = integer_n / NUMBER_OF_THREADS;
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int thread_count = omp_get_num_threads();
        long from = local_steps * thread_id;
        long to = from + local_steps;

        /**
         * The last thread will have to do more work because some integer_n will not be divisible by NUMBER_OF_THREADS
         */
        if (thread_id == (thread_count - 1)) {
            to += integer_n % thread_count;
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


long parallel_summation_using_promotion_of_scalar(long integer_n) {
    long promoted_total_sum[NUMBER_OF_THREADS];
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        promoted_total_sum[thread_id] = 0l;
        for (long local_begin = thread_id; local_begin <= integer_n; local_begin += 4) {
            promoted_total_sum[thread_id] += local_begin;
        }
    };
    long actual_total_sum = 0;
    for (int a = 0; a < NUMBER_OF_THREADS; a++) {
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

