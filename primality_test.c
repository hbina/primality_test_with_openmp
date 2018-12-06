//
// Created by hbina on 01/12/18.
//

#include "primality_test.h"
#include <stdio.h>
#include <assert.h>
#include <omp.h>

unsigned long long get_first_prime_divisor(unsigned long long integer_of) {
    if (integer_of <= 1ull) {
        return 1ull;
    } else if (!(integer_of % 2ull)) {
        return 2ull;
    } else {
        for (unsigned long long integer_from = 3ull; integer_from * integer_from <= integer_of; integer_from += 2ull) {
            if (integer_of % integer_from == 0ull) {
#if ENABLE_VERBOSE
                printf("first prime divisor of %llu is %llu\n", integer_of, integer_from);
#endif
                return integer_from;
            }
        }
#if ENABLE_VERBOSE
        printf("first prime divisor of %llu is itself\n", integer_of);
#endif
        return integer_of;
    }
}

int local_primality_test(
        unsigned long long integer_of,
        unsigned long long integer_from,
        unsigned long long integer_to) {
    if (integer_of <= 1ull) {
        return false;
    } else if (!(integer_of % 2ull)) {
        return false;
    } else {
        for (; integer_from <= integer_to; integer_from += 2ull) {
            if (integer_of % integer_from == 0ull) return 0;
        }
        return 1;
    }
}

int serial_primality_test(unsigned long long integer_n) {
    return local_primality_test(integer_n, 3, integer_n / 2);
}

int parallel_primality_test_basic(unsigned long long integer_n) {
#if ENABLE_VERBOSE
    printf("testing primality on %llu\n", integer_n);
#endif
    if (integer_n <= 1ull) return false;
    if (!(integer_n % 2ull)) {
        return false;
    } else {
        int is_prime = true;
        unsigned long long local_steps = integer_n / 8ull;
        if (!(local_steps % 2)) local_steps++;
#pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            unsigned long long local_begin = thread_id * local_steps;
            if (local_begin < 3ull) local_begin = 3;
            if (!(local_begin % 2ull)) local_begin--;
            unsigned long long local_end = local_begin + local_steps;
            if (!(local_end % 2ull)) local_end--;
            for (; local_begin <= local_end; local_begin += 2ull) {
                if (integer_n % local_begin == 0) {
#if ENABLE_VERBOSE
                    printf("failed on %llu\n", local_begin);
#endif
                    is_prime = false;
                }
            }
        };
        return is_prime;
    }
}

void verify_primality_test_on_primes(
        int (*prime_function)(unsigned long long int),
        unsigned long long *prime_examples,
        int num_of_prime_examples
) {
#if ENABLE_VERBOSE
    printf("verifying primality test on primes\n");
#endif
    for (int a = 0; a < num_of_prime_examples; a++) {
        int is_prime = prime_function(prime_examples[a]);
        assert(is_prime == true);
    }
}

void verify_primality_test_on_non_primes(
        int (*prime_function)(unsigned long long int),
        unsigned long long *prime_examples,
        int num_of_prime_examples
) {
#if ENABLE_VERBOSE
    printf("verifying primality test on non-primes\n");
#endif
    for (int a = 0; a < num_of_prime_examples; a++) {
        int is_prime = prime_function(prime_examples[a]);
        assert(is_prime == false);
    }
}

int parallel_primality_test_sentinel(unsigned long long integer_n) {
#if ENABLE_VERBOSE
    printf("testing primality on %llu\n", integer_n);
#endif
    if (integer_n <= 1ull) return false;
    if (!(integer_n % 2ull)) {
        return false;
    } else {
        int is_prime = true;
#pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            unsigned long long local_steps = integer_n / 2ull;
            local_steps /= ((unsigned long long) omp_get_num_threads());
            if (!(local_steps % 2ull)) local_steps++;
            unsigned long long local_begin = thread_id * local_steps;
            if (local_begin < 3ull) local_begin = 3;
            if (!(local_begin % 2ull)) local_begin--;
            unsigned long long local_end = local_begin + local_steps;
            if (!(local_end % 2ull)) local_end--;
            for (; local_begin <= local_end; local_begin += 2ull) {
                if (integer_n % local_begin == 0) {
#if ENABLE_VERBOSE
                    printf("failed on %llu\n", local_begin);
#endif
                    is_prime = false;
                    local_begin = local_end;
                }
                if (!is_prime) {
                    local_begin = local_end;
                }
            }
        };
        return is_prime;
    }
}