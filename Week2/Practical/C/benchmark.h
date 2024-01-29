// Both
typedef struct
{
    double min;
    double max;
    double mean;
    double sigma;
    int number_of_points;
} results;

void stats_on_results(results *data, double *time_values, int num_points)
{
    int i;
    // Get the mean
    double sum = 0;
    for (i = 0; i < num_points; i++)
    {
        sum = sum + time_values[i];
    }
    data->mean = sum / (double)num_points;
    // Get the standard deviation
    double std_sum = 0;
    for (i = 0; i < num_points; i++)
    {
        std_sum = std_sum + (time_values[i] - data->mean) * (time_values[i] - data->mean);
    }
    data->sigma = sqrt(std_sum / (double)num_points);
    // Get the minimum time
    double min = time_values[0];
    for (i = 1; i < num_points; i++)
    {
        if (time_values[i] < min)
        {
            min = time_values[i];
        }
    }
    data->min = min;
    // Get the maximum time
    double max = time_values[0];
    for (i = 1; i < num_points; i++)
    {
        if (time_values[i] > max)
        {
            max = time_values[i];
        }
    }
    data->max = max;
    data->number_of_points = num_points;
}
// OpenMP
results *benchmark(int num_thread, int array_size, int num_runs)
{
    int *a;
    double *time_values;
    double start;
    double end;
    results *output_results = (results *)malloc(sizeof(results));
    omp_set_num_threads(num_thread);
    // Allocate the timing array
    time_values = (double *)malloc(num_runs * sizeof(double));
    int i;
    for (i = 0; i < num_runs; i++)
    {
        time_values[i] = 0.0;
    }
    // Allocate the a array
    a = (int *)malloc(array_size * sizeof(int));
    int j;
    for (j = 0; j < num_runs; j++)
    {
        // Reset the array
        for (i = 0; i < array_size; i++)
        {
            a[i] = 0;
        }
        start = omp_get_wtime();
#pragma omp parallel for private(i) shared(a) num_threads(num_thread)
        for (i = 0; i < array_size; i++)
        {
            a[i] = a[i] + 2;
        }
        end = omp_get_wtime();
        time_values[j] = end - start;
    }
    stats_on_results(output_results, time_values, num_runs);
    free(time_values);
    free(a);
    return output_results;
}

results *benchmark_single(int num_thread, int array_size, int num_runs)
{
    int *a;
    double *time_values;
    double start;
    double end;
    results *output_results = (results *)malloc(sizeof(results));
    // Allocate the timing array
    time_values = (double *)malloc(num_runs * sizeof(double));
    int i;
    for (i = 0; i < num_runs; i++)
    {
        time_values[i] = 0.0;
    }
    // Allocate the a array
    a = (int *)malloc(array_size * sizeof(int));
    int j;
    for (j = 0; j < num_runs; j++)
    {
        // Reset the array
        for (i = 0; i < array_size; i++)
        {
            a[i] = 0;
        }
        start = omp_get_wtime();
        for (i = 0; i < array_size; i++)
        {
            a[i] = a[i] + 2;
        }
        end = omp_get_wtime();
        time_values[j] = end - start;
    }
    stats_on_results(output_results, time_values, num_runs);
    free(time_values);
    free(a);
    return output_results;
}
// MPI
void allocate_a_and_t(int num_runs, int array_size, double *time_array, int *a_array)
{
    int i;
    for (i = 0; i < num_runs; i++)
    {
        time_array[i] = 0.0;
    }
    for (i = 0; i < array_size; i++)
    {
        a_array[i] = 0;
    }
}

int get_my_len_per_process(int array_size, int size, int rank)
{
    int len_per_process = array_size / size;
    int remainder = array_size % size;
    int mylen_per_process = (rank < remainder) ? (len_per_process + 1) : (len_per_process);
    return mylen_per_process;
}

void displs_and_a_per_proc(int *displs, int size, int *recvcounts, int *a_per_process, int mylen_per_process)
{
    int i;
    displs[0] = 0;
    for (i = 1; i < size; i++)
    {
        displs[i] = displs[i - 1] + recvcounts[i - 1];
    }

    for (i = 0; i < mylen_per_process; i++)
    {
        a_per_process[i] = 0.0;
    }
}

void add_2_to_array(int *a_per_process, int mylen_per_process)
{
    int j;
    for (j = 0; j < mylen_per_process; j++)
    {
        a_per_process[j] = a_per_process[j] + 2.0;
    }
}