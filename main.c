#include <stdio.h>
#include <omp.h>
#include <assert.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
// TODO: Implement False Sharing, PADDING, Barrier, Mutual Exclusion

int main() {
    verify_serial_summation();
    verify_parallel_summation_using_promotion_of_scalar();
    verify_parallel_summation_using_block();
    verify_parallel_summation_using_critical();
    benchmark_wrapper(&parallel_summation_using_critical);
    return 0;
}