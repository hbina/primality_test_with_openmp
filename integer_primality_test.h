//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H

#define true 1
#define false 0


unsigned long long get_first_prime_divisor(unsigned long long);

int local_primality_test(unsigned long long, unsigned long long, unsigned long long);

int serial_primality_test(unsigned long long);

int parallel_primality_test_basic(unsigned long long);

int parallel_primality_test_sentinel(unsigned long long);

void verify_primality_test_on_primes(int (*)(unsigned long long), unsigned long long *, int);

void verify_primality_test_on_non_primes(int (*)(unsigned long long), unsigned long long *, int);

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
