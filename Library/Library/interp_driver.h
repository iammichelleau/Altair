#include <time.h>
#include <cmath>
#include "interp.h"

#define N 300
#define L (2*N + 1)
#define M_PI 3.14159265359
#define MAX 2*M_PI
#define MIN -2*M_PI

void initialization(double *, double *);
void free(double *, double *, double *, double *, double *);
void test(double *, double *, double *, double *, double, OSINT *, OSINT);
