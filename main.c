#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
#include "integer_primality_test.h"

#define MAX_INTEGER_IN_LOG_10 10
#define MAX_INTEGER_IN_LOG_2 32
#define NUM_OF_PRIME_EXAMPLES 6
typedef struct {
    double serial_summation;
    double parallel_summation_using_promotion_of_scalar;
    double parallel_summation_using_atomic;
    double parallel_summation_using_critical;
} summation_statistics;

typedef struct {

    double serial_primality_test;
    double parallel_primality_test_using_promotion_of_scalar;
    double parallel_primality_test_using_sentinel;
} primality_statistics;

unsigned long long primes_example[6] = {
        //263148883742208227l,
        //4211612917736675431l,
        //1870964419912864547l,
        //2219262178829073559l,
        556640177l,
        622192141l,
        3427376149l,
        1461729319l,
        1823204723l,
        2787253289l
};

unsigned long long ipow(unsigned long long base, unsigned char exp) {
    for (unsigned char a = 0; a < exp; a++) {
        base *= base;
    }
    return base;
}

int main() {
    summation_statistics summation_stats = {0};
    primality_statistics primality_stats = {0};

    unsigned long long max_integer_pow10 = ipow(2l, (unsigned long long int) MAX_INTEGER_IN_LOG_2);

    verify_summation(
            serial_summation,
            max_integer_pow10);
    printf("serial summation tests passed\n");
    verify_summation(
            parallel_summation_using_promotion_of_scalar,
            max_integer_pow10);
    printf("parallel summation using promotion of scalar tests passed\n");

    verify_summation(
            parallel_summation_using_atomic,
            max_integer_pow10);
    printf("parallel summation using atomic tests passed\n");

    verify_summation(
            parallel_summation_using_critical,
            max_integer_pow10);
    printf("parallel summation using critical tests passed\n");
    verify_primality_test(
            serial_primality_test,
            primes_example,
            NUM_OF_PRIME_EXAMPLES);
    printf("serial primality test tests passed\n");
    verify_primality_test(
            parallel_primality_test_using_promotion_of_scalar,
            primes_example,
            NUM_OF_PRIME_EXAMPLES);
    printf("parallel primality test using promotion of scalar verification tests passed\n");

    verify_primality_test(
            parallel_primality_test_using_sentinel,
            primes_example,
            NUM_OF_PRIME_EXAMPLES);
    printf("parallel primality test using sentinel verification tests passed\n");

    for (unsigned char integer_n = 0; integer_n < MAX_INTEGER_IN_LOG_2; integer_n++) {
        summation_stats.serial_summation += addition_benchmark_wrapper(
                &serial_summation, max_integer_pow10);
        summation_stats.parallel_summation_using_promotion_of_scalar += addition_benchmark_wrapper(
                &parallel_summation_using_promotion_of_scalar, max_integer_pow10);
        summation_stats.parallel_summation_using_atomic += addition_benchmark_wrapper(
                &parallel_summation_using_atomic, max_integer_pow10);
        summation_stats.parallel_summation_using_critical += addition_benchmark_wrapper(
                &parallel_summation_using_critical, max_integer_pow10);
    }

    for (int a = 0; a < 10; a++) {
        primality_stats.serial_primality_test += primality_test_benchmark_wrapper(
                &serial_primality_test,
                primes_example,
                NUM_OF_PRIME_EXAMPLES);
        primality_stats.parallel_primality_test_using_promotion_of_scalar +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_using_promotion_of_scalar,
                        primes_example,
                        NUM_OF_PRIME_EXAMPLES);

        primality_stats.parallel_primality_test_using_sentinel +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_using_sentinel,
                        primes_example,
                        NUM_OF_PRIME_EXAMPLES);
    }

    printf("serial_primality_test:\n%e\n", primality_stats.serial_primality_test / 10);
    printf("parallel_primality_test_using_promotion_of_scalar:\n%e\n",
           primality_stats.parallel_primality_test_using_promotion_of_scalar / 10);
    printf("parallel_primality_test_using_sentinel:\n%e\n",
           primality_stats.parallel_primality_test_using_sentinel / 10);
    return 0;
}