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

unsigned long long large_prime_examples[NUM_OF_LARGE_PRIME_EXAMPLES] = {
        345345342347l,
        345345342373l,
        345345342379l,
        345345342389l,
        345345342403l,
        345345342439l
};

unsigned long long small_prime_examples[NUM_OF_SMALL_PRIME_EXAMPLES] = {
        7507l,
        7517l,
        7523l,
        7529l,
        7537l,
        7541l
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

    printf("serial_primality_test:\n%e\n", primality_stats.serial_primality_test / number_of_prime_examples);
    printf("parallel_primality_test_using_promotion_of_scalar:\n%e\n",
           primality_stats.parallel_primality_test_using_promotion_of_scalar / number_of_prime_examples);
    printf("parallel_primality_test_using_sentinel:\n%e\n",
           primality_stats.parallel_primality_test_using_sentinel / number_of_prime_examples);
}

int main() {
    printf("verifying primality test of small primes\n");
    verify_primality_test(
            serial_primality_test,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    printf("serial primality test tests passed\n");
    verify_primality_test(
            parallel_primality_test_using_promotion_of_scalar,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    printf("parallel primality test using promotion of scalar verification tests passed\n");
    verify_primality_test(
            parallel_primality_test_using_sentinel,
            small_prime_examples,
            NUM_OF_SMALL_PRIME_EXAMPLES);
    printf("parallel primality test using sentinel verification tests passed\n");

    printf("verifying primality test of large primes\n");
    verify_primality_test(
            serial_primality_test,
            large_prime_examples,
            NUM_OF_LARGE_PRIME_EXAMPLES);
    printf("serial primality test tests passed\n");
    verify_primality_test(
            parallel_primality_test_using_promotion_of_scalar,
            large_prime_examples,
            NUM_OF_LARGE_PRIME_EXAMPLES);
    printf("parallel primality test using promotion of scalar verification tests passed\n");
    verify_primality_test(
            parallel_primality_test_using_sentinel,
            large_prime_examples,
            NUM_OF_LARGE_PRIME_EXAMPLES);
    printf("parallel primality test using sentinel verification tests passed\n");

    printf("primality test performance on large integers\n");
    benchmark_primality_test(large_prime_examples, NUM_OF_LARGE_PRIME_EXAMPLES);
    printf("\n\nprimality test performance on small integers\n");
    benchmark_primality_test(small_prime_examples, NUM_OF_SMALL_PRIME_EXAMPLES);
    return 0;
}