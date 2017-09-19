#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <time.h>
#include "bicubic.h"

#define N 100

extern OSINT X;
extern OSINT MAX_X;
extern OSINT Y;

void raw_initialization(OSINT **, double **, double ****);
void initialization(double **, double **, double ****, OSINT **);
void free(OSINT *, OSINT *, OSINT *, OSINT *, OSINT *, double *, double *, double *, double *, double *, double *, double *,
          double *, double *, double *, OSINT *, double *, double *, double **, double ***, double ***);
void read_input(string, OSINT **, double **, double ****);
void get_dimensions(string);
void get_values(string, double **, double ****);
void test(double, double, double *, double *);

vector<string> split(const string &, char);
OSINT *ivector(long nl, long nh);
