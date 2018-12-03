//
// Created by hbina on 01/12/18.
//

#include "integer_primality_test.h"
#include <stdio.h>
#include <assert.h>
#include <omp.h>

char
local_primality_test(unsigned long long integer_of, unsigned long long integer_from, unsigned long long integer_to) {
    if (!integer_of) {
        return false;
    } else if (integer_of == 1l) {
        return true;
    } else if (!(integer_of % 2l)) {
        return false;
    } else {
        while ((integer_of % integer_from) && (integer_from < integer_to)) {
            integer_from += 2l;
        }
        return integer_of == integer_from;
    }
}

char serial_primality_test(unsigned long long integer_n) {
    return local_primality_test(integer_n, 3, integer_n);
}

char parallel_primality_test_using_promotion_of_scalar(unsigned long long integer_n) {
    if (integer_n < 100) {
        return serial_primality_test(integer_n);
    } else if (!(integer_n % 2l)) {
        return false;
    } else {
        char is_prime[4] = {1};
        unsigned long long local_steps = integer_n / 4l;
        unsigned long long local_ends[] = {
                local_steps,
                2 * local_steps,
                3 * local_steps,
                4 * local_steps
        };
        printf("local_steps:%llu 0:%llu 1:%llu 2:%llu 3:%llu\n",
               local_steps,
               local_ends[0],
               local_ends[1],
               local_ends[2],
               local_ends[3]
        );
#pragma omp parallel num_threads(4)
        {
            int thread_id = omp_get_thread_num();
            unsigned long long local_begin = thread_id * local_steps;
            if (local_begin < 3) local_begin = 3;
            unsigned long long local_end = local_ends[thread_id];
            printf("thread_id:%d local_begin:%llu local_end:%llu\n", thread_id, local_begin, local_end);
            is_prime[thread_id] = local_primality_test(integer_n, local_begin, local_end);
        };
        char final_bool = false;
        for (int a = 0; a < omp_get_max_threads(); a++) {
            final_bool |= is_prime[a];
        }
        return final_bool;
    }
}

void verify_primality_test(
        char (*prime_function)(unsigned long long int),
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

char parallel_primality_test_using_sentinel(unsigned long long integer_n) {
    if (integer_n < 100) {
        return serial_primality_test(integer_n);
    } else if (!(integer_n % 2l)) {
        return false;
    } else {
        char is_prime[4] = {1};
        unsigned long long local_steps = integer_n / 4l;
        unsigned long long local_ends[] = {
                local_steps,
                2 * local_steps,
                3 * local_steps,
                4 * local_steps
        };
        printf("local_steps:%llu 0:%llu 1:%llu 2:%llu 3:%llu\n",
               local_steps,
               local_ends[0],
               local_ends[1],
               local_ends[2],
               local_ends[3]
        );
#pragma omp parallel num_threads(4)
        {
            int thread_id = omp_get_thread_num();
            unsigned long long local_begin = thread_id * local_steps;
            if (local_begin < 3) local_begin = 3;
            unsigned long long local_end = local_ends[thread_id];
            printf("thread_id:%d local_begin:%llu local_end:%llu\n", thread_id, local_begin, local_end);
            is_prime[thread_id] = local_primality_test(integer_n, local_begin, local_end);
        };
        char final_bool = false;
        for (int a = 0; a < omp_get_max_threads(); a++) {
            final_bool |= is_prime[a];
        }
        return final_bool;
    }
}
