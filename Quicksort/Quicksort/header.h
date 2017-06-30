#pragma once

#define OSINT int
#define M 7
#define NSTACK 64
#define NR_END 1

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <time.h>

using namespace std;

void initialization(OSINT N, OSINT *istack, OSINT *index, OSINT *A_int, OSINT *B_int, OSINT *temp_int,
                    OSINT *A_int_orig, OSINT *B_int_orig, double *A_double, double *B_double,
                    double *temp_double, double *A_double_orig, double *B_double_orig); 
OSINT *ivector(long nl, long nh);
void free_ivector(OSINT *v, long nl, long nh);
void swap(OSINT &a, OSINT &b);
void swap(double &a, double &b);

void sort(OSINT *A_orig, OSINT *B_orig, OSINT *A, OSINT *B, OSINT *istack, OSINT *index, OSINT *temp_int, double *temp_double, OSINT N);
void sort(double *A_orig, OSINT *B_orig, double *A, OSINT *B, OSINT *istack, OSINT *index, OSINT *temp_int, double *temp_double, OSINT N);
void sort(OSINT *A_orig, double *B_orig, OSINT *A, double *B, OSINT *istack, OSINT *index, OSINT *temp_int, double *temp_double, OSINT N);
void sort(double *A_orig, double *B_orig, double *A, double *B, OSINT *istack, OSINT *index, OSINT *temp_int, double *temp_double, OSINT N);

void quicksort(OSINT *A, OSINT *istack, OSINT N);
void quicksort(double *A, OSINT *istack, OSINT N);

void get_index(OSINT *temp, OSINT *A, OSINT *index, OSINT N);
void get_index(double *temp, double *A, OSINT *index, OSINT N); 
void sort_by_index(OSINT *B, OSINT *index, OSINT *temp, OSINT N);
void sort_by_index(double *B, OSINT *index, double *temp, OSINT N);


void print(OSINT *A, OSINT N);
void print(double *A, OSINT N);

void test_increasing(OSINT *A, OSINT N);
void test_increasing(double *A, OSINT N);
void test_order(OSINT *orig, OSINT *sorted, OSINT *index, OSINT N);
void test_order(double *orig, double *sorted, OSINT *index, OSINT N);















