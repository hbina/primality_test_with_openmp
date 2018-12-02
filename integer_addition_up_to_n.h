//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H


/**
 * HELPER FUNCTIONS
 */

unsigned long long local_integer_summation(unsigned long long, unsigned long long);

unsigned long long formula_summation(unsigned long long integer_n);

/**
 * LIST OF SUMMATION TECHNIQUE
 */

void verify_summation(unsigned long long(*)(unsigned long long), unsigned long long);

unsigned long long serial_summation(unsigned long long);

unsigned long long parallel_summation_using_promotion_of_scalar(unsigned long long);

unsigned long long parallel_summation_using_atomic(unsigned long long);

unsigned long long parallel_summation_using_critical(unsigned long long);

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
