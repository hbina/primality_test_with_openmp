#include <stdio.h>
#include <omp.h>
#include <assert.h>
#include "benchmark_wrapper.h"
#include "integer_addition_up_to_n.h"
// TODO: Implement False Sharing, PADDING, Barrier, Mutual Exclusion

int main() {
    verify_summation_of_n();
    benchmark_wrapper(begin_test_integer_summation);
    return 0;
}