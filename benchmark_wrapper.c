//
// Created by hbina on 01/12/18.
//

#include <omp.h>
#include <stdio.h>

void benchmark_wrapper(long (*function_to_benchmark)(long)) {
    double t_begin = omp_get_wtime();
    for (long integer_n = 1; integer_n < 1000; integer_n++){
        function_to_benchmark(integer_n);
    }
    double t_diff = omp_get_wtime() - t_begin;
    printf("completion takes %e seconds\n", t_diff);
}