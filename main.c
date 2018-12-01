#include <stdio.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
// TODO: Implement False Sharing, PADDING, Barrier, Mutual Exclusion

int main() {
    verify_serial_summation();
    verify_parallel_summation_using_promotion_of_scalar();
    verify_parallel_summation_using_barrier();
    verify_parallel_summation_using_critical();

    printf("serial_summation\n");
    benchmark_wrapper(&serial_summation);

    printf("parallel_summation_using_promotion_of_scalar\n");
    benchmark_wrapper(&parallel_summation_using_promotion_of_scalar);

    printf("parallel_summation_using_barrier\n");
    benchmark_wrapper(&parallel_summation_using_barrier);

    printf("parallel_summation_using_atomic\n");
    benchmark_wrapper(&parallel_summation_using_atomic);

    printf("parallel_summation_using_critical\n");
    benchmark_wrapper(&parallel_summation_using_critical);
    return 0;
}