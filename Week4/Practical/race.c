#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>

int main(void){

  int i, j, n, tid, nthreads, *a;

  /* Enter the array size */
  printf("Please enter the size of the array\n");
  scanf("%d",&n);
  if (n<2 || n>1000) {
    printf(" Enter a positive number in range 2<n<10001\n");
    exit(1);
  }

  a = (int *) malloc(n*sizeof(int));
  if (a == NULL) {
    printf(" Cannot allocate array for id %d, stopping\n",tid);
    exit(2);
  }

  a[0] = 0;

  /* Start of parallel region */
#pragma omp parallel private(i,j,tid), shared(nthreads,n,a)
{
  tid=omp_get_thread_num();
  nthreads=omp_get_num_threads();
  /* Generate different random numbers */
  srand(time(NULL)*tid);
  
  a[0] = a[0] + rand()%11;

  /* Set all elements per thread equal */
  for (j=1; j<n; j++) a[j] = a[0];
    printf("Hello from thread %d out of %d my a is: %d\n", tid,nthreads,a[0]);
} /* end parallel region */

  /* Check that value from last thread saved */
  printf("Hello from the master thread my a is: %d\n",a[0]);

  free(a);

  return 0;
}
