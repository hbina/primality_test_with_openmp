//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H

#define true 1
#define false 0


int local_primality_test(unsigned long long, unsigned long long, unsigned long long);

int serial_primality_test(unsigned long long);

int parallel_primality_test_using_promotion_of_scalar(unsigned long long);

int parallel_primality_test_using_sentinel(unsigned long long);

void verify_primality_test_on_primes(int (*)(unsigned long long), unsigned long long *, int);

void verify_primality_test_on_non_primes(int (*)(unsigned long long), unsigned long long *, int);

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
