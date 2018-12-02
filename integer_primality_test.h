//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H

#define true 1
#define false 0


char local_primality_test(unsigned long long, unsigned long long, unsigned long long);

char serial_primality_test(unsigned long long);

void verify_serial_primality_test();

char parallel_primality_test_using_promotion_of_scalar(unsigned long long);

void verify_parallel_primality_test_using_promotion_of_scalar(unsigned long long *, int);

char parallel_primality_test_using_atomic(unsigned long long);

void verify_parallel_primality_test_using_atomic();

char parallel_primality_test_using_critical(unsigned long long);

void verify_parallel_primality_test_using_critical();

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
