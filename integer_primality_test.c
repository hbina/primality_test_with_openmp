//
// Created by hbina on 01/12/18.
//

#include "integer_primality_test.h"
#include <stdio.h>
#include <assert.h>
#include <omp.h>


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
            if (integer_of % integer_from == 0) return 0;
        }
        return 1;
    }
}

int serial_primality_test(unsigned long long integer_n) {
    return local_primality_test(integer_n, 3, integer_n / 2);
}

int parallel_primality_test_using_promotion_of_scalar(unsigned long long integer_n) {
    if (integer_n <= 1ull) return false;
    if (!(integer_n % 2ull)) {
        return false;
    } else {
        int is_prime[4] = {true, true, true, true};
        unsigned long long local_steps = integer_n / 8ull;
        if (!(local_steps % 2)) local_steps++;
#pragma omp parallel num_threads(4)
        {
            int local_is_prime = true;
            int thread_id = omp_get_thread_num();
            unsigned long long local_begin = thread_id * local_steps;
            if (local_begin < 3ull) local_begin = 3;
            if (!(local_begin % 2ull)) local_begin--;
            unsigned long long local_end = local_begin + local_steps;
            if (!(local_end % 2ull)) local_end--;
            for (; local_begin <= local_end; local_begin += 2ull) {
                if (integer_n % local_begin == 0) {
                    local_is_prime = false;
                    goto end;
                }
            }
            end:
            is_prime[thread_id] = local_is_prime;
        };
        int final_bool = true;
        for (int a = 0; a < 4; a++) {
            final_bool &= is_prime[a];
        }
        return final_bool;
    }
}

void verify_primality_test(
        int (*prime_function)(unsigned long long int),
        unsigned long long *prime_examples,
        int num_of_prime_examples
) {
    for (unsigned long long integer_n = 4; integer_n < 1000l; integer_n += 2l) {
        assert(prime_function(integer_n) == false);
    }
    printf("the following integers should be prime\n");
    for (int a = 0; a < num_of_prime_examples; a++) {
        // assert(prime_function(prime_examples[a]) == true);
        printf("%llu is prime:%d\n", prime_examples[a], prime_function(prime_examples[a]));
    }
    printf("the following integers should not be prime\n");
    for (int a = 0; a < num_of_prime_examples; a++) {
        unsigned long long not_prime = prime_examples[a] - 2;
        // assert(prime_function(not_prime) == false);
        printf("%llu is prime:%d\n", not_prime, prime_function(not_prime));
    }
}

int parallel_primality_test_using_sentinel(unsigned long long integer_n) {
    if (integer_n <= 1ull) return false;
    if (!(integer_n % 2ull)) {
        return false;
    } else {
        int is_prime[4] = {true, true, true, true};
        unsigned long long local_steps = integer_n / 8ull;
        if (!(local_steps % 2)) local_steps++;
#pragma omp parallel num_threads(4)
        {
            int local_is_prime = true;
            int thread_id = omp_get_thread_num();
            unsigned long long local_begin = thread_id * local_steps;
            if (local_begin < 3ull) local_begin = 3;
            if (!(local_begin % 2ull)) local_begin--;
            unsigned long long local_end = local_begin + local_steps;
            if (!(local_end % 2ull)) local_end--;
            for (; local_begin <= local_end; local_begin += 2ull) {
                if (integer_n % local_begin == 0) {
                    local_is_prime = false;
                    goto end;
                }
                int final_is_prime = true;
                for (int a = 0; a < 4; a++) {
                    final_is_prime &= is_prime[a];
                }
                if (!final_is_prime){
                    goto end;
                }
            }
            end:
            is_prime[thread_id] = local_is_prime;
        };
        int final_bool = true;
        for (int a = 0; a < 4; a++) {
            final_bool &= is_prime[a];
        }
        return final_bool;
    }
}
