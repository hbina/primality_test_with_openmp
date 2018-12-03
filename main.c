#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_primality_test.h"

#define NUM_OF_SMALL_PRIME_EXAMPLES 6
#define NUM_OF_LARGE_PRIME_EXAMPLES 6
typedef struct {
    double serial_summation;
    double parallel_summation_using_promotion_of_scalar;
    double parallel_summation_using_atomic;
    double parallel_summation_using_critical;

    double serial_primality_test;
    double parallel_primality_test_using_promotion_of_scalar;
    double parallel_primality_test_using_sentinel;
} primality_statistics;


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

void benchmark_primality_test(unsigned long long *examples, int number_of_prime_examples) {
    primality_statistics primality_stats = {0};
    for (int a = 0; a < number_of_prime_examples; a++) {
        primality_stats.serial_primality_test += primality_test_benchmark_wrapper(
                &serial_primality_test,
                examples[a]);
        primality_stats.parallel_primality_test_using_promotion_of_scalar +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_using_promotion_of_scalar,
                        examples[a]);

        primality_stats.parallel_primality_test_using_sentinel +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_using_sentinel,
                        examples[a]);
    }

    //printf("serial_primality_test:\n%e\n", primality_stats.serial_primality_test / number_of_prime_examples);
    printf("parallel_primality_test_using_promotion_of_scalar:\n%e\n",
           primality_stats.parallel_primality_test_using_promotion_of_scalar / number_of_prime_examples);
    printf("parallel_primality_test_using_sentinel:\n%e\n",
           primality_stats.parallel_primality_test_using_sentinel / number_of_prime_examples);
}

int main() {

#if VERBOSE
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
#if VERBOSE
    printf("serial primality test tests passed\n");
#endif
#if VERBOSE
    printf("verifying parallel primality test using promotion of scalar\n");
#endif
    verify_primality_test_on_primes(
            parallel_primality_test_using_promotion_of_scalar,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    verify_primality_test_on_non_primes(
            parallel_primality_test_using_promotion_of_scalar,
            small_non_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
#if VERBOSE
    printf("parallel primality test using promotion of scalar verification tests passed\n");
#endif
#if VERBOSE
    printf("verifying parallel primality test using sentinel\n");
#endif
    verify_primality_test_on_primes(
            parallel_primality_test_using_sentinel,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    verify_primality_test_on_non_primes(
            parallel_primality_test_using_sentinel,
            small_non_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);

#if VERBOSE
    printf("parallel primality test using sentinel verification tests passed\n");
#endif
#if VERBOSE
    printf("\n\nprimality test performance on small prime integers\n");
#endif
    benchmark_primality_test(small_prime_examples, NUM_OF_SMALL_PRIME_EXAMPLES);
#if VERBOSE
    printf("\n\nprimality test performance on small non-prime integers\n");
#endif
    benchmark_primality_test(small_non_prime_examples, NUM_OF_SMALL_PRIME_EXAMPLES);
    return 0;
}