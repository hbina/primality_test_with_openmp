//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H

#define test_until_n 10


/**
 * HELPER FUNCTIONS
 */

long local_integer_summation(long, long);

long formula_summation(long integer_n);

/**
 * LIST OF SUMMATION TECHNIQUE
 */


long serial_summation(long integer_n);

void verify_serial_summation();

long parallel_summation_using_promotion_of_scalar(long integer_n);

void verify_parallel_summation_using_promotion_of_scalar();

long parallel_summation_using_atomic(long integer_n);

void verify_parallel_summation_using_atomic();

long parallel_summation_using_critical(long integer_n);

void verify_parallel_summation_using_critical();

long parallel_summation_using_barrier(long integer_n);

void verify_parallel_summation_using_barrier();

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
