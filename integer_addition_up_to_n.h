//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H

#define test_until_n 1000

void begin_test_integer_summation();

/**
 * LIST OF SUMMATION TECHNIQUE
 */

long formula_summation(long integer_n);

long serial_summation(long n);

void verify_serial_summation();

long parallel_summation_using_promotion_of_scalar(long integer_n);

void verify_parallel_summation_using_promotion_of_scalar();

long parallel_summation_using_critical(long n);

void verify_parallel_summation_using_critical();

long parallel_summation_using_block(long n);

void verify_parallel_summation_using_block();

/**
 * HELPER FUNCTIONS
 */

long local_integer_summation(long, long);


void verify_serial_summation();

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
