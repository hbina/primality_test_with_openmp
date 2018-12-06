#include <stdio.h>
#include "benchmark_wrapper.h"
#include "primality_test.h"

#define NUM_OF_SMALL_PRIME_EXAMPLES 6

unsigned long long small_prime_examples[NUM_OF_SMALL_PRIME_EXAMPLES] = {
        1000000007ull,
        1000000009ull,
        1000000021ull,
        1000000033ull,
        1000000087ull,
        1000000093ull
};

unsigned long long small_non_prime_examples[NUM_OF_SMALL_PRIME_EXAMPLES] = {
        1000000011ull,
        1000000015ull,
        1000000017ull,
        1000000019ull,
        1000000023ull,
        1000000025ull
};

int main() {

#if ENABLE_UNIT_TEST
#if ENABLE_VERBOSE
    printf("verifying serial primality test\n");
#endif
    verify_primality_test_on_primes(
            serial_primality_test,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    verify_primality_test_on_non_primes(
            serial_primality_test,
            small_non_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
#if ENABLE_VERBOSE
    printf("serial primality test tests passed\n");
#endif
#if ENABLE_VERBOSE
    printf("verifying parallel primality test using promotion of scalar\n");
#endif
    verify_primality_test_on_primes(
            parallel_primality_test_basic,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    verify_primality_test_on_non_primes(
            parallel_primality_test_basic,
            small_non_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
#if ENABLE_VERBOSE
    printf("parallel primality test using promotion of scalar verification tests passed\n");
#endif
#if ENABLE_VERBOSE
    printf("verifying parallel primality test using sentinel\n");
#endif
    verify_primality_test_on_primes(
            &parallel_primality_test_sentinel,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    verify_primality_test_on_non_primes(
            &parallel_primality_test_sentinel,
            small_non_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
#if ENABLE_VERBOSE
    printf("parallel primality test using sentinel verification tests passed\n");
#endif
#endif

#if ENABLE_BENCMARK
#if ENABLE_VERBOSE
    printf("\n\nprimality test performance on small prime integers\n");
#endif
    benchmark_primality_test(small_prime_examples, NUM_OF_SMALL_PRIME_EXAMPLES);
#if ENABLE_VERBOSE
    printf("\n\nprimality test performance on small non-prime integers\n");
#endif
    benchmark_primality_test(small_non_prime_examples, NUM_OF_SMALL_PRIME_EXAMPLES);
#endif
    benchmark_find_all_primes(100000000ull, &parallel_primality_test_sentinel);
    return 0;
}