#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int testprime(int i);

int main(void) {

     int i,j,n,nprimes,nsqroot,*primes;


     printf(" Enter the maximum number you want to find as prime\n");
     scanf("%d",&n);


     /* Parallel region */


     return 0;


}


int testprime(int i) {
    int j, nsqroot;

    nsqroot = ceil(sqrt((float) i)) + 1;
    if (nsqroot >= i) nsqroot = i - 1;


    j = 2;
    while (i%j!=0 && j<=nsqroot) j++;

   if (j>nsqroot) {
     return 0;
   } else {
     return 1;
   }
}