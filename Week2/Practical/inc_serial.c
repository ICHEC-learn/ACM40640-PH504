/*****************************************************************************
* DESCRIPTION:
* This program increments every element of the array by two.
* Compile: 
*	$gcc inc_serial.c -o inc_serialc -fopenmp 
* Run:
* 	$./inc_serialc <array length> <nSamples>
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main (int argc, char* argv[])
{
  int i, j;
  long length, nSamples;
  double *a;
  double start, end;

  /*Get array length and number of times to run the computation*/
  if (argc!=3) {
    printf("Wrong number of arguments!!! \n");
    printf("usage: %s  <array length> <nSamples>\n",argv[0]);
    return -1;
  }
  length=atoi(argv[1]);
  nSamples=atoi(argv[2]);

  /*Array Allocation and Initialisation*/
  a = (double*) malloc (length*sizeof(double));
  for (i=0; i<length; i++){
    a[i]=0.0;
  }

  /*Increment elements by 2*/
  start=omp_get_wtime(); 
  for (i=0; i<nSamples; i++) {
    for (j=0; j<length; j++){
      a[j]=a[j]+2.0;  
    }
  }  
  end=omp_get_wtime();

  /*Check correctness*/
  for(i=0; i<length; i++){
    if(a[i]!=2.0*nSamples){
      printf("Not equal at %d\n", i);
      break;
    }
  }

  printf ("Size=%ld, Average Execution Time=%lfsec\n", length, (end-start)/nSamples);

  free(a);
  return 0;
}   
