/*****************************************************************************
* DESCRIPTION:
* This program increments every element of the array by two.
* using mpi.
* Compile: 
*	$mpicc inc_mpi.c -o inc_mpic -fopenmp
* Run:
* 	$mpirun -np 2 ./inc_mpic <array length> <nSamples>
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

int main (int argc, char* argv[])
{
  int i, j, len_per_process, remainder, mylen_per_process;
  long length, nSamples;
  int size, rank;
  int *recvcounts, *displs;
  double *a, *a_per_process;
  double start_comp, start_comm, end_comp, end_comm, maxtime_comp, maxtime_comm;

  /*Get array length and number of times to run the computation*/
  if (argc!=3) {
    printf("Wrong number of arguments!!! \n");
    printf("usage: %s  <array length> <nSamples>\n",argv[0]);
    return -1;
  }
  length=atoi(argv[1]);
  nSamples=atoi(argv[2]);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  /*Whole array allocation in master process*/
  if(rank==0){
    a=(double*) malloc (length*sizeof(double));
  }
  recvcounts=(int*) malloc (size*sizeof(int));
  displs=(int*) malloc (size*sizeof(int));

  /*Data distribution to processes*/
  len_per_process = length/size; 
  remainder = length%size;
  mylen_per_process = (rank<remainder)?(len_per_process+1):(len_per_process);
  
  MPI_Allgather(&mylen_per_process, 1, MPI_INT, recvcounts, 1, MPI_INT, MPI_COMM_WORLD);
  displs[0] = 0;
  for(i=1; i<size; i++) {
    displs[i] = displs[i-1] + recvcounts[i-1];
  }

  /*Sub-Arrays Allocation and Initialisation at each process*/
  a_per_process = (double*) malloc (mylen_per_process*sizeof(double));
  for (i=0; i<mylen_per_process; i++){
    a_per_process[i]=0.0;
  }

  /*Increment elements by 2*/
  start_comp=omp_get_wtime(); 
  for (i=0; i<nSamples; i++) {
    for (j=0; j<mylen_per_process; j++){
      a_per_process[j]=a_per_process[j]+2.0;  
    }
  }  
  end_comp=omp_get_wtime()-start_comp;
  start_comm=omp_get_wtime(); 
  MPI_Gatherv(a_per_process, mylen_per_process, MPI_DOUBLE, a, recvcounts, displs, MPI_DOUBLE, 0, MPI_COMM_WORLD); 
  end_comm=omp_get_wtime()-start_comm;

  /*Check correctness*/
  for(i=0; i<length; i++){
    if(rank==0){
      if(a[i]!=2.0*nSamples){
        printf("Not equal at %d\n", i);
        break;
      }
    }
  }

  MPI_Reduce(&end_comp, &maxtime_comp, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  MPI_Reduce(&end_comm, &maxtime_comm, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  if(rank==0){
    printf ("Size=%ld, Number of processes=%d\n", length, size);
    printf ("Computation Time= %lf sec, Communication Time=  %lf sec\n", maxtime_comp/nSamples, maxtime_comm);
  }

  free(a_per_process);
  free(recvcounts);
  free(displs);
  if(rank==0){
    free(a);
  }
  MPI_Finalize();
  return 0;
}   
