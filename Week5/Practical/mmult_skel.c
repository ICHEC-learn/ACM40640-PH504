#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

struct matrix {
   int nrow;
   int ncol;
   float *matrix;
};

int getindex(struct matrix m, int i, int j);


int main(void) {
   int i,j,k;
   struct matrix a, b, c;
   FILE *fp;

/* Read in the matrix sizes */
   printf(" Enter size of A (row,column)\n");
   scanf("%d, %d",&a.nrow,&a.ncol);
   printf(" Matrix A rows=%d columns=%d\n",a.nrow,a.ncol);

   printf(" Enter size of B (row,column)\n");
   scanf("%d, %d",&b.nrow,&b.ncol);
   printf(" Matrix A rows=%d columns=%d\n",b.nrow,b.ncol);

/* Check values */
   if (a.ncol != b.nrow) {
     printf(" These matrices cannot be multiplied, stopping\n");
     exit(1);
   } else {
     c.nrow = a.nrow;
     c.ncol = b.ncol;
   }

/* Assign space */

/* Generate random arrays */

/* Perform A.B */

/* Write to a file */

}


int getindex(struct matrix m, int i, int j){

    return m.ncol*i + j;
}
 