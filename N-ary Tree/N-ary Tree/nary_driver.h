#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <time.h>
#include "nary.h"

#define DIM 4

extern OSINT LEAVES;
extern OSINT LENGTH; 

void raw_initialization(double ***, OSINT **, OSINT **);
void initialization(double **, double **, double **, OSINT **);
void read_input(string, double ***, OSINT **, OSINT **);
void get_dimensions(string);
void get_values(string, double ***);
void test(double, double *, double *, OSINT *, OSINT *);

vector<string> split(const string &, char);
