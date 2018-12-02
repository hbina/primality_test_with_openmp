#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
#include "integer_primality_test.h"

#define HOW_MANY_TIMES 1000
#define MAX_INTEGER_FOR_SUMMATION 100000
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
    summation_statistics summation_stats[HOW_MANY_TIMES];
    primality_statistics primality_stats = {0, 0};
    verify_serial_summation(MAX_INTEGER_FOR_SUMMATION);
    verify_parallel_summation_using_promotion_of_scalar(MAX_INTEGER_FOR_SUMMATION);
    verify_parallel_summation_using_atomic(MAX_INTEGER_FOR_SUMMATION);
    verify_parallel_summation_using_critical(MAX_INTEGER_FOR_SUMMATION);

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

    for (int a = 0; a < HOW_MANY_TIMES; a++) {
        summation_stats[a].serial_summation = addition_benchmark_wrapper(&serial_summation);
        summation_stats[a].parallel_summation_using_promotion_of_scalar = addition_benchmark_wrapper(
                &parallel_summation_using_promotion_of_scalar);
        summation_stats[a].parallel_summation_using_atomic = addition_benchmark_wrapper(
                &parallel_summation_using_atomic);
        summation_stats[a].parallel_summation_using_critical = addition_benchmark_wrapper(
                &parallel_summation_using_critical);
    }
    FILE *gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "plot '-'\n");
    for (int i = 0; i < HOW_MANY_TIMES; i++)
        fprintf(gnuplot, "%d %e\n", i, summation_stats[i].serial_summation);
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);
    for (int a = 0; a < HOW_MANY_TIMES; a++) {
        primality_stats.serial_primality_test += primality_test_benchmark_wrapper(
                &serial_primality_test,
                primes_example,
                NUM_OF_PRIME_EXAMPLES);

        primality_stats.parallel_primality_test_using_promotion_of_scalar +=
                primality_test_benchmark_wrapper(
                        &parallel_primality_test_using_promotion_of_scalar,
                        primes_example,
                        NUM_OF_PRIME_EXAMPLES);
    }
    printf("serial_primality_test:\n%e\n", primality_stats.serial_primality_test / HOW_MANY_TIMES);
    printf("parallel_primality_test_using_promotion_of_scalar:\n%e\n",
           primality_stats.parallel_primality_test_using_promotion_of_scalar / HOW_MANY_TIMES);

    return 0;
}