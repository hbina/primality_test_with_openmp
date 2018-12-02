//
// Created by hbina on 01/12/18.
//

#include "integer_primality_test.h"
#include <stdio.h>
#include <assert.h>
#include <omp.h>

#define test_until_n 10

unsigned long long primes_example[] = {
        //263148883742208227l,
        //4211612917736675431l,
        //1870964419912864547l,
        //2219262178829073559l,
        556640177l,
        622192141l,
        3427376149l,
        1461729319l,
        1823204723l,
        2787253289
};

char
local_primality_test(unsigned long long integer_of, unsigned long long integer_from, unsigned long long integer_to) {
    if (!integer_of) return false;
    if (!(integer_of % 2l)) {
        return false;
    }
    unsigned long long integer_odd_counter = integer_from;
    while (integer_of % integer_odd_counter && integer_odd_counter < integer_to) { integer_odd_counter += 2l; }
    return (char) (integer_of == integer_odd_counter);
}

char serial_primality_test(unsigned long long integer_n) {
    local_primality_test(integer_n, 3, integer_n);
}

void verify_serial_primality_test() {
    for (unsigned long long integer_n = 2; integer_n < test_until_n; integer_n += 2l) {
        assert(serial_primality_test(integer_n) == 0);
        serial_primality_test(integer_n);
    }
    assert(serial_primality_test(3) == true);
    assert(serial_primality_test(5) == true);
    assert(serial_primality_test(7) == true);
    assert(serial_primality_test(9) == false);
    assert(serial_primality_test(11) == true);
    assert(serial_primality_test(13) == true);
    assert(serial_primality_test(15) == false);
    assert(serial_primality_test(17) == true);
    assert(serial_primality_test(19) == true);
    assert(serial_primality_test(21) == false);
    printf("serial primality test verification tests passed\n");
}

char parallel_primality_test_using_promotion_of_scalar(unsigned long long integer_n) {
    if (integer_n <= omp_get_max_threads() * omp_get_max_threads()) {
        return serial_primality_test(integer_n);
    } else if (!(integer_n % 2l)) {
        return false;
    } else {
        char isPrime[NUMBER_OF_THREADS] = {1};
        unsigned long long local_steps = integer_n / NUMBER_OF_THREADS;
#pragma omp parallel
        {
            int thread_id = omp_get_thread_num();
            unsigned long long local_begin = local_steps * thread_id;
            if (local_begin < 3l)
                local_begin = 3l; // this is true for thread_id==0 because local_begin will be less than 3, starts with at least 3 for god's sake
            if (!(local_begin % 2l))
                local_begin++; // if local_begin somehow is divisible by 2, then just increment to get odd value
            unsigned long long local_end = local_begin + local_steps;
            if (local_end == integer_n)
                local_end -= 2l; // this is true for thread_id == NUMBER_OF_THREADS, just decrement by 2 to get the previous odd number
            for (; local_begin < local_end; local_begin += 2l) {
                if (!(integer_n % local_begin)) {
                    isPrime[thread_id] = false;
                    local_begin = local_end;
                }
            }
        };
        char final_bool = false;
        for (int a = 0; a < NUMBER_OF_THREADS; a++) {
            final_bool |= isPrime[a];
        }
        return final_bool;
    }
}

void verify_parallel_primality_test_using_promotion_of_scalar() {
    for (unsigned long long integer_n = 4; integer_n < test_until_n; integer_n += 2l) {
        assert(parallel_primality_test_using_promotion_of_scalar(integer_n) == false);
    }
    for (int a = 0; a < 6; a++) {
        printf("testing:%llu\n", primes_example[a]);
        assert(parallel_primality_test_using_promotion_of_scalar(primes_example[a]) == true);
    }
    printf("parallel primality test using promotion of scalar verification tests passed\n");
}