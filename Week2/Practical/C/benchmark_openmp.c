

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "benchmark.h"

int main(int argc, char *argv[])
{
    FILE *pFile;
    int size_1 = 1000000;
    int size_2 = 10000000;
    int size_3 = 100000000;
    int size_4 = 1000000000;
    pFile = fopen("openmp_results", "a");
    fprintf(pFile, "Num_threads\t10^6\t10^7\t10^8\t10^9\n");
    //  Iterate through doing the calculation for the job sizes and thread numbers
    int thread_count = 1;
    for (thread_count = 1; thread_count < 101; thread_count++)
    {
        printf("This is with %d threads\n", thread_count);
        results *r1 = benchmark(thread_count, size_1, 10);
        results *r2 = benchmark(thread_count, size_2, 10);
        results *r3 = benchmark(thread_count, size_3, 10);
        results *r4 = benchmark(thread_count, size_4, 10);
        fprintf(pFile, "%d\t%.16f\t%.16f\t%.16f\t%.16f\n", thread_count, r1->mean, r2->mean, r3->mean, r4->mean);
        free(r1);
        free(r2);
        free(r3);
        free(r4);
    }
    return 0;
}
