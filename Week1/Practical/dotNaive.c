/*
    Copyright (c) 2014 Alin Marin Elena <alinm.elena@gmail.com>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <omp.h>

double dot(double *A,double *B, int n);

int main(int argc, char **argv)
{

  int n;
  double z;
  int i,j;

  if (argc!=3) {
    printf("Wrong number of arguments!!! \n");
    printf("usage: %s  n NSamples\n",argv[0]);
    return -1;
  }

  n=atoi(argv[1]);
  int nSamples=atoi(argv[2]);
  printf("Running... ");
  for(i=0; i<argc; ++i) {
    printf("%s ",argv[i]);
  }
  printf("\n");

  double *times = (double *) malloc(nSamples*sizeof(double));
  double *A = (double *) malloc(n*sizeof(double));
  double *B = (double *) malloc(n*sizeof(double));
  double tmin=DBL_MAX;
  double tmax=0.0;
  for (i=1; i<=nSamples; ++i) {
    for (j=0; j<n; ++j) {
      A[j] = (double) i * (double)(j+1)/(double) n;
      B[j] = (double) i * ((double)j+1.5)/(double) n;
    }
    times[i-1] = omp_get_wtime();
    z=dot(A,B,n);
    times[i-1] = omp_get_wtime()-times[i-1];
    if (tmin>times[i-1]) tmin=times[i-1];
    if (tmax<times[i-1]) tmax=times[i-1];

  }
  double timeAvg = 0.0;
  for(i=0; i<nSamples; ++i) {
    timeAvg+=times[i];
  }
  timeAvg/=nSamples;

  double sig=0.0;
  for(i=0; i<nSamples; ++i) {
    sig+=(times[i]-timeAvg)*(times[i]-timeAvg);
  }
  sig=sqrt(sig/nSamples);

  printf("#Loop  |       Size|        Time (s)|\n");
  for(i=0; i<nSamples; ++i) {
    printf("%6d %12d %16.8f\n",i+1,n,times[i]);
  }
  printf("\nLast inner product: %16.8E\n",z);
  printf("\nSummary:\n");
  printf("#Size  n    |  Avg. Time (s) |   Min. Time(s) |   Max. Time(s) | σ Time(s)\n");
  printf("%12d %16.8f %16.8f %16.8f %16.8f\n",n,timeAvg,tmin,tmax,sig);

  free(times);
  free(A);
  free(B);
  return 0;
}

double dot(double *A,double *B, int n)
{
  int i;
  double s=0.0d;
  for(i=0; i<n; ++i) {
    s+=A[i]*B[i];
  }
  return s;
}
