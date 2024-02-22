#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

int n, *primes;

void removenums(int i);
int testprime(int i);

int main(void) {
    int i,nprimes,ierr,tid;


    printf(" What is the highest number you want to test?\n");
    scanf("%d",&n);
    if (n < 2) {
      printf("Number must be bigger than 1, stopping\n");
      exit(1);
    }

    primes = (int *) malloc(n*sizeof(int));

    if (primes == NULL) {
       printf(" Cannot allocate array, stopping\n");
       exit(2);
    }

    for (i=0; i<n; i++) primes[i] = i+1;
    primes[0] = -1;



}


int testprime(int i) {
    int  j,nsqroot;

/* Add one because array index added not number */
    i = i+1;

/* sqrt is the largest that needs to be checked */
    nsqroot = ceil(sqrt((float) i)) + 1;
    if (nsqroot >= i) nsqroot--;

    j = 2;
    while (i%j!=0 && j<=nsqroot) j++;
  
/* If not divisible by any of the numbers it must be prime */
    if (j > nsqroot) {
       return 0;
    } else {
       return 1;
    }
}

void removenums(int i) {
    int j;

    j = (i+1)*2;
    while (j < n) {
      primes[j-1] = -1;
      j = j + i+1;
    }
}