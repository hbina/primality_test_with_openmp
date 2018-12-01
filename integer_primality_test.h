//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H

#define true 1
#define false 0

char serial_primality_test(long integer_n);

void verify_serial_primality_test();

char parallel_primality_test_using_promotion_of_scalar(long integer_n);

void verify_parallel_primality_test_using_promotion_of_scalar();

char parallel_primality_test_using_atomic(long integer_n);

void verify_parallel_primality_test_using_atomic();

char parallel_primality_test_using_critical(long integer_n);

void verify_parallel_primality_test_using_critical();

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
