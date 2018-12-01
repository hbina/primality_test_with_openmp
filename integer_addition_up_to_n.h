//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H

#define test_until_n 100000

void begin_test_integer_summation();

long integer_summation(long n);

long local_integer_summation(long, long);

/**
 * SERIAL CALCULATION
 */

long serial_summation(long n);

/**
 * DEBUGGING
 */
void verify_summation_of_n();

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_ADDITION_UP_TO_N_H
