#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>
#include "biinterp.h"

#define N 100
#define XMIN -4
#define XMAX 4
#define YMIN -1
#define YMAX 1

OSINT Q = 1; // # of y-values
OSINT M = 1; // max # of x-values

void read_input(string, double ****);
void get_dimensions(string);
void get_values(string, double ****);
vector<string> split(const string &, char);
void initialization(double ****);
void free(double ****);
void test(double, double, OSINT *, OSINT *, double ***, double *);
