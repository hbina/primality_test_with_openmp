#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
#include "integer_primality_test.h"

#define HOW_MANY_TIMES 100
struct benchmark_statistics {
    double serial_summation;
    double parallel_summation_using_promotion_of_scalar;
    double parallel_summation_using_atomic;
    double parallel_summation_using_critical;
} statistics;

int main() {
    if (0) {
        statistics.serial_summation = 0l;
        statistics.parallel_summation_using_promotion_of_scalar = 0l;
        statistics.parallel_summation_using_atomic = 0l;
        statistics.parallel_summation_using_critical = 0l;
        verify_serial_summation();
        verify_parallel_summation_using_promotion_of_scalar();
        verify_parallel_summation_using_atomic();
        verify_parallel_summation_using_critical();

        for (int a = 0; a < HOW_MANY_TIMES; a++) {
            statistics.serial_summation += benchmark_wrapper(&serial_summation);
            statistics.parallel_summation_using_promotion_of_scalar += benchmark_wrapper(
                    &parallel_summation_using_promotion_of_scalar);
            statistics.parallel_summation_using_atomic += benchmark_wrapper(&parallel_summation_using_atomic);
            statistics.parallel_summation_using_critical += benchmark_wrapper(&parallel_summation_using_critical);
        }
        printf("serial_summation:\n%e\n", statistics.serial_summation / HOW_MANY_TIMES);
        printf("parallel_summation_using_promotion_of_scalar:\n%e\n",
               statistics.parallel_summation_using_promotion_of_scalar / HOW_MANY_TIMES);
        printf("summation_parallel_summation_using_atomic:\n%e\n",
               statistics.parallel_summation_using_atomic / HOW_MANY_TIMES);
        printf("parallel_summation_using_critical:\n%e\n",
               statistics.parallel_summation_using_critical / HOW_MANY_TIMES);
    }

    verify_serial_primality_test();
    return 0;
}