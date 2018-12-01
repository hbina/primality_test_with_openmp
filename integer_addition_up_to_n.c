//
// Created by hbina on 01/12/18.
//
#include <assert.h>
#include <omp.h>
#include <stdio.h>
#include "integer_addition_up_to_n.h"


#define number_of_threads 4

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

long parallel_summation_using_barrier(long n) {
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
#pragma omp barrier
        total_sum += local_sum;
    };
    return total_sum;
}

void verify_parallel_summation_using_barrier() {
    for (long a = 0; a < test_until_n; a++) {
        long formula_summation = a * (a + 1) / 2;
        assert(formula_summation == parallel_summation_using_barrier(a));
    }
    printf("parallel summation using barrier verification tests passed\n");
}


long parallel_summation_using_promotion_of_scalar(long integer_n) {
    long promoted_total_sum[number_of_threads];
//    printf("integer_n:%ld", integer_n);
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        promoted_total_sum[thread_id] = 0l;
        for (long local_begin = thread_id; local_begin <= integer_n; local_begin += omp_get_thread_num()) {
            //  printf("thread_id:%d local_begin:%ld\n\n", thread_id, local_begin);
            promoted_total_sum[thread_id] += local_begin;
        }
    };
    long actual_total_sum = 0;
    for (int a = 0; a < number_of_threads;
         a++) {
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

