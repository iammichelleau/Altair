#pragma once

#include <iostream>
#include <cmath>
#include "qsort.h"

using namespace std;

#define OSINT int
#define INF 1e36

OSINT handle_input(double *, OSINT *, OSINT *, OSINT);

void uniform_grid(double *, double *, double *, OSINT *, double *, double ****, double ***, 
	OSINT, OSINT, OSINT); 
void make_grid(double *, double ***, double ****, OSINT, OSINT, OSINT);
void interp_grid(double ****, OSINT, OSINT, OSINT *, double *, double *, double *);

OSINT simple(double *, double *, double, OSINT *, double *, OSINT);
void get_results(double *, double *, double, OSINT *, double*, OSINT);
bool in_between(double, double, double);

void bicubic_interp(double, double, OSINT *, OSINT *, OSINT *,
                    double *, double *, double *, double *, double *, double *,
                    double ***, double ***, OSINT, OSINT, double *);
void locate(double, double, OSINT *, OSINT *, double ***, OSINT, OSINT);
void derivatives(double, double, OSINT *, OSINT *, double ***, OSINT, OSINT,
                 double *, double *, double *, double *);
void bcucof(OSINT *, double *, double *, double *, double *, double *, double *, double, double, double ***);
void bcuint(double, double, OSINT *, OSINT *, double ***, double **, double *);
