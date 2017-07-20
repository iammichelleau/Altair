#include <time.h>
#include <cmath>
#include "interp.h"

#define M_PI 3.14159265359
#define MAX 2*M_PI
#define MIN -2*M_PI

void initialization(double *, double *);
void free(double *, double *, double *, double *, double *);
void test(double *, double *, double *, double *, double, OSINT *, OSINT);
