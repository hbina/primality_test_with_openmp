#include <stdio.h>
#include <omp.h>
#include <assert.h>

// TODO: Implement False Sharing, PADDING, Barrier, Mutual Exclusion
void benchmark_wrapper(void (*function_to_benchmark)());

#define test_until_n 10000
#define num_threads 4

void test_integer_summation();

int integer_summation(int n);

int local_integer_summation(int, int);

void verify_summation_of_n();

int main() {
    //verify_summation_of_n();
    benchmark_wrapper(test_integer_summation);
    return 0;
}

void verify_summation_of_n() {
    for (int a = 0; a < test_until_n; a++) {
        int formula_summation = a * (a + 1) / 2;
        assert(formula_summation == integer_summation(a));
    }
}

void benchmark_wrapper(void (*function_to_benchmark)()) {
    double t_begin = omp_get_wtime();
    function_to_benchmark();
    double t_diff = omp_get_wtime() - t_begin;
    printf("completion takes %e seconds", t_diff);
}


void test_integer_summation() {
    for (int a = 1; a < test_until_n; a++) {
        integer_summation(a);
    }
}

int integer_summation(int n) {
    int total_sum = 0;
    int local_steps = n / num_threads;
#pragma omp parallel
    {
        int from = local_steps * omp_get_thread_num();
        int to = from + local_steps;

        if (omp_get_thread_num() == (omp_get_num_threads() - 1)) {
            to += n % omp_get_num_threads();
            to += 1;
        }
        int local_sum = local_integer_summation(from, to);
#pragma omp critical
        total_sum += local_sum;
    };
    return total_sum;
}

int local_integer_summation(int from, int to) {
    int sum = 0;
    for (; from < to; from++) {
        sum += from;
    }
    return sum;
}