#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qsort.h"

void initialization(OSINT N, OSINT *istack, OSINT *index, OSINT *A_int, OSINT *B_int, OSINT *temp_int,
                    OSINT *A_int_orig, OSINT *B_int_orig, double *A_double, double *B_double,
                    double *temp_double, double *A_double_orig, double *B_double_orig);
void free(OSINT *istack, OSINT *index, OSINT *A_int, OSINT *B_int, OSINT *temp_int,
          OSINT *A_int_orig, OSINT *B_int_orig, double *A_double, double *B_double,
          double *temp_double, double *A_double_orig, double *B_double_orig);

void print(OSINT *A, OSINT N);
void print(double *A, OSINT N);

void test_increasing(OSINT *A, OSINT N);
void test_increasing(double *A, OSINT N);
void test_order(OSINT *orig, OSINT *sorted, OSINT *index, OSINT N);
void test_order(double *orig, double *sorted, OSINT *index, OSINT N);

OSINT *ivector(long nl, long nh);
