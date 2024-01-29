

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <mpi.h>
#include "benchmark.h"

int main(int argc, char *argv[])
{
    int size, rank, num_runs, array_size;
    int *a, *a_per_process, *recvcounts, *displs;
    double *time_values;
    double start, end, maxtime;
    int len_per_process, remainder, mylen_per_process;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    num_runs = 2;
    FILE *pFile;
    int size_1 = 1000000;
    int size_2 = 10000000;
    int size_3 = 100000000;
    int size_4 = 1000000000;
    // Generate the time and value arrays on process 0
    int i;
    int k;
    pFile = fopen("mpi_results.txt", "a");
    if (size == 1)
    {
        fprintf(pFile, "Num_threads\t10^6\t10^7\t10^8\t10^9\n");
    }
    array_size = size_1;
    if (rank == 0)
    {
        time_values = (double *)malloc(num_runs * sizeof(double));
        a = (int *)malloc(array_size * sizeof(int));
        allocate_a_and_t(num_runs, array_size, time_values, a);
    }
    results *output_results1 = (results *)malloc(sizeof(results));
    for (k = 0; k < num_runs; k++)
    {
        recvcounts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));
        mylen_per_process = get_my_len_per_process(array_size, size, rank);
        MPI_Allgather(&mylen_per_process, 1, MPI_INT, recvcounts, 1, MPI_INT, MPI_COMM_WORLD);
        a_per_process = (int *)malloc(mylen_per_process * sizeof(int));
        displs_and_a_per_proc(displs, size, recvcounts, a_per_process, mylen_per_process);
        start = omp_get_wtime();
        add_2_to_array(a_per_process, mylen_per_process);
        end = omp_get_wtime() - start;
        MPI_Gatherv(a_per_process, mylen_per_process, MPI_INT, a, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Reduce(&end, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if (rank == 0)
        {
            time_values[k] = maxtime;
        }
        free(a_per_process);
        free(recvcounts);
        free(displs);
    }
    if (rank == 0)
    {
        stats_on_results(output_results1, time_values, num_runs);
    }
    array_size = size_2;
    results *output_results2 = (results *)malloc(sizeof(results));
    if (rank == 0)
    {
        time_values = (double *)malloc(num_runs * sizeof(double));
        a = (int *)malloc(array_size * sizeof(int));
        allocate_a_and_t(num_runs, array_size, time_values, a);
    }

    for (k = 0; k < num_runs; k++)
    {
        recvcounts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));
        mylen_per_process = get_my_len_per_process(array_size, size, rank);
        MPI_Allgather(&mylen_per_process, 1, MPI_INT, recvcounts, 1, MPI_INT, MPI_COMM_WORLD);
        a_per_process = (int *)malloc(mylen_per_process * sizeof(int));
        displs_and_a_per_proc(displs, size, recvcounts, a_per_process, mylen_per_process);
        start = omp_get_wtime();
        add_2_to_array(a_per_process, mylen_per_process);
        end = omp_get_wtime() - start;
        MPI_Gatherv(a_per_process, mylen_per_process, MPI_INT, a, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Reduce(&end, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if (rank == 0)
        {
            time_values[k] = maxtime;
        }
        free(a_per_process);
        free(recvcounts);
        free(displs);
    }

    if (rank == 0)
    {

        stats_on_results(output_results2, time_values, num_runs);
    }
    array_size = size_3;
    results *output_results3 = (results *)malloc(sizeof(results));
    if (rank == 0)
    {
        time_values = (double *)malloc(num_runs * sizeof(double));
        a = (int *)malloc(array_size * sizeof(int));
        allocate_a_and_t(num_runs, array_size, time_values, a);
    }

    for (k = 0; k < num_runs; k++)
    {
        recvcounts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));
        mylen_per_process = get_my_len_per_process(array_size, size, rank);
        MPI_Allgather(&mylen_per_process, 1, MPI_INT, recvcounts, 1, MPI_INT, MPI_COMM_WORLD);
        a_per_process = (int *)malloc(mylen_per_process * sizeof(int));
        displs_and_a_per_proc(displs, size, recvcounts, a_per_process, mylen_per_process);
        start = omp_get_wtime();
        add_2_to_array(a_per_process, mylen_per_process);
        end = omp_get_wtime() - start;
        MPI_Gatherv(a_per_process, mylen_per_process, MPI_INT, a, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Reduce(&end, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if (rank == 0)
        {
            time_values[k] = maxtime;
        }
        free(a_per_process);
        free(recvcounts);
        free(displs);
    }

    if (rank == 0)
    {

        stats_on_results(output_results3, time_values, num_runs);
    }
    array_size = size_4;
    results *output_results4 = (results *)malloc(sizeof(results));
    if (rank == 0)
    {
        time_values = (double *)malloc(num_runs * sizeof(double));
        a = (int *)malloc(array_size * sizeof(int));
        allocate_a_and_t(num_runs, array_size, time_values, a);
    }

    for (k = 0; k < num_runs; k++)
    {
        recvcounts = (int *)malloc(size * sizeof(int));
        displs = (int *)malloc(size * sizeof(int));
        mylen_per_process = get_my_len_per_process(array_size, size, rank);
        MPI_Allgather(&mylen_per_process, 1, MPI_INT, recvcounts, 1, MPI_INT, MPI_COMM_WORLD);
        a_per_process = (int *)malloc(mylen_per_process * sizeof(int));
        displs_and_a_per_proc(displs, size, recvcounts, a_per_process, mylen_per_process);
        start = omp_get_wtime();
        add_2_to_array(a_per_process, mylen_per_process);
        end = omp_get_wtime() - start;
        MPI_Gatherv(a_per_process, mylen_per_process, MPI_INT, a, recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Reduce(&end, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if (rank == 0)
        {
            time_values[k] = maxtime;
        }
        free(a_per_process);
        free(recvcounts);
        free(displs);
    }

    if (rank == 0)
    {
        stats_on_results(output_results4, time_values, num_runs);
    }

    if (rank == 0)
    {
        fprintf(pFile, "%d\t%.16f\t%.16f\t%.16f\t%.16f\n", size, output_results1->mean, output_results2->mean, output_results3->mean, output_results4->mean);
    }
    free(output_results1);
    free(output_results2);
    free(output_results3);
    free(output_results4);
    MPI_Finalize();
    return 0;
}
