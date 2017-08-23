#include <iostream>
#include <cmath>

#define OSINT int
#define QSORT_M 7
#define NSTACK 64
#define NR_END 1

using namespace std;

void sort(OSINT *A_orig, OSINT *B_orig, OSINT *A, OSINT *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N);
void sort(double *A_orig, OSINT *B_orig, double *A, OSINT *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N);
void sort(OSINT *A_orig, double *B_orig, OSINT *A, double *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N);
void sort(double *A_orig, double *B_orig, double *A, double *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N);

void quicksort(OSINT *A, OSINT *index, OSINT *istack, OSINT N);
void quicksort(double *A, OSINT *index, OSINT *istack, OSINT N);
void sort_by_index(OSINT *B, OSINT *index, OSINT *temp, OSINT N);
void sort_by_index(double *B, OSINT *index, double *temp, OSINT N);

void swap(OSINT &a, OSINT &b);
void swap(double &a, double &b);
