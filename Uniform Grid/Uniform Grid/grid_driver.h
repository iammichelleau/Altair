#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <time.h>
#include "grid.h"

extern OSINT X;
extern OSINT MAX_X;
extern OSINT Y;

void initialization(OSINT **, double **, double ****);
void free(OSINT *, OSINT *, OSINT *, OSINT *, OSINT *, double *, double *, double *, double *, double *,
          double *, double *, double *, double **, double ***, double ***);
void read_input(string, OSINT **, double **, double ****);
void get_dimensions(string);
void get_values(string, double **, double ****);
void theo(OSINT, double, double, double *);

void print(OSINT *A, OSINT N);
void print(double *A, OSINT N);

vector<string> split(const string &, char);
OSINT *ivector(long nl, long nh);
