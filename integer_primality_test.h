//
// Created by hbina on 01/12/18.
//

#ifndef PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
#define PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H

#define true 1
#define false 0


char local_primality_test(unsigned long long, unsigned long long, unsigned long long);

char serial_primality_test(unsigned long long);

char parallel_primality_test_using_promotion_of_scalar(unsigned long long);

char parallel_primality_test_using_sentinel(unsigned long long);

void
verify_primality_test(char (*)(unsigned long long), unsigned long long *, int);

#endif //PERFORMANCE_OF_PRIME_PRIMALITY_INTEGER_PRIMALITY_TEST_H
