//
// Created by hbina on 01/12/18.
//

#include <omp.h>
#include <stdio.h>

void benchmark_wrapper(void (*function_to_benchmark)()) {
    double t_begin = omp_get_wtime();
    function_to_benchmark();
    double t_diff = omp_get_wtime() - t_begin;
    printf("completion takes %e seconds", t_diff);
}