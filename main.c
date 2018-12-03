#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_primality_test.h"

#define MAX_INTEGER_IN_LOG_10 10
#define MAX_INTEGER_IN_LOG_2 32
#define NUM_OF_SMALL_PRIME_EXAMPLES 10
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
        556640177l,
        622192141l,
        3427376149l,
        1461729319l,
        1823204723l,
        2787253289l,
};

unsigned long long small_prime_examples[NUM_OF_SMALL_PRIME_EXAMPLES] = {
        1009l,
        1013l,
        1019l,
        1021l,
        1031l,
        1033l,
        1039l,
        1049l,
        1051l,
        1061l
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
    primality_statistics primality_stats = {0};
    /**
    verify_summation(
            serial_summation,
            1000);
    printf("serial summation tests passed\n");
    verify_summation(
            parallel_summation_using_promotion_of_scalar,
            1000);
    printf("parallel summation using promotion of scalar tests passed\n");

    verify_summation(
            parallel_summation_using_atomic,
            1000);
    printf("parallel summation using atomic tests passed\n");

    verify_summation(
            parallel_summation_using_critical,
            1000);
    printf("parallel summation using critical tests passed\n");
     **/
    printf("veryfying primality test of large primes\n");
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

    printf("veryfying primality test of small primes\n");
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
    /**
    double number_of_tests = 0.0f;
    for (unsigned long long integer_n = 0; integer_n < MAX_INTEGER_IN_LOG_2; integer_n++) {
        primality_stats.serial_summation += addition_benchmark_wrapper(
                &serial_summation, integer_n);
        primality_stats.parallel_summation_using_promotion_of_scalar += addition_benchmark_wrapper(
                &parallel_summation_using_promotion_of_scalar, integer_n);
        primality_stats.parallel_summation_using_atomic += addition_benchmark_wrapper(
                &parallel_summation_using_atomic, integer_n);
        primality_stats.parallel_summation_using_critical += addition_benchmark_wrapper(
                &parallel_summation_using_critical, integer_n);
        number_of_tests++;
    }
    printf("serial_summation:\n%e\n", primality_stats.serial_summation / number_of_tests);
    printf("parallel_summation_using_promotion_of_scalar:\n%e\n",
           primality_stats.parallel_summation_using_promotion_of_scalar / number_of_tests);
    printf("parallel_summation_using_atomic:\n%e\n",
           primality_stats.parallel_summation_using_atomic / number_of_tests);
    printf("parallel_summation_using_critical:\n%e\n",
           primality_stats.parallel_summation_using_critical / number_of_tests);

     **/
    printf("primality test performance on large integers\n");
    benchmark_primality_test(large_prime_examples, NUM_OF_LARGE_PRIME_EXAMPLES);
    printf("\n\nprimality test performance on small integers\n");
    benchmark_primality_test(small_prime_examples, NUM_OF_SMALL_PRIME_EXAMPLES);
    return 0;
}