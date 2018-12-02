#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
#include "integer_primality_test.h"

#define HOW_MANY_TIMES 100
#define MAX_INTEGER_FOR_SUMMATION 100000
#define PRIMALITY_TEST_START 1000
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

int main() {
    summation_statistics summation_stats[MAX_INTEGER_FOR_SUMMATION];
    primality_statistics primality_stats = {0, 0, 0};

    /**
    verify_summation(serial_summation, MAX_INTEGER_FOR_SUMMATION);
    printf("serial summation tests passed\n");
     **/

    verify_summation(parallel_summation_using_promotion_of_scalar, MAX_INTEGER_FOR_SUMMATION);
    printf("parallel summation using promotion of scalar tests passed\n");

    verify_summation(parallel_summation_using_atomic, MAX_INTEGER_FOR_SUMMATION);
    printf("parallel summation using atomic tests passed\n");

    verify_summation(parallel_summation_using_critical, MAX_INTEGER_FOR_SUMMATION);
    printf("parallel summation using critical tests passed\n");

    /**
    verify_primality_test(
            serial_primality_test,
            primes_example,
            NUM_OF_PRIME_EXAMPLES);
    printf("serial primality test tests passed\n");
**/
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

    for (int integer_n = 0; integer_n < MAX_INTEGER_FOR_SUMMATION; integer_n++) {
        summation_stats[integer_n].serial_summation = addition_benchmark_wrapper(
                &serial_summation, (unsigned long long int) integer_n);
        summation_stats[integer_n].parallel_summation_using_promotion_of_scalar = addition_benchmark_wrapper(
                &parallel_summation_using_promotion_of_scalar, (unsigned long long int) integer_n);
        summation_stats[integer_n].parallel_summation_using_atomic = addition_benchmark_wrapper(
                &parallel_summation_using_atomic, (unsigned long long int) integer_n);
        summation_stats[integer_n].parallel_summation_using_critical = addition_benchmark_wrapper(
                &parallel_summation_using_critical, (unsigned long long int) integer_n);
    }
    printf("drawing\n");
    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < MAX_INTEGER_FOR_SUMMATION; i++)
        fprintf(gnuplot, "%d %e\n", i, summation_stats[i].parallel_summation_using_critical);
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);
    for (int a = 0; a < HOW_MANY_TIMES; a++) {
        /**
        primality_stats.serial_primality_test += primality_test_benchmark_wrapper(
                &serial_primality_test,
                primes_example,
                NUM_OF_PRIME_EXAMPLES);
        **/
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
    printf("serial_primality_test:\n%e\n", primality_stats.serial_primality_test / HOW_MANY_TIMES);
    printf("parallel_primality_test_using_promotion_of_scalar:\n%e\n",
           primality_stats.parallel_primality_test_using_promotion_of_scalar / HOW_MANY_TIMES);
    printf("parallel_primality_test_using_sentinel:\n%e\n",
           primality_stats.parallel_primality_test_using_sentinel / HOW_MANY_TIMES);
    return 0;
}