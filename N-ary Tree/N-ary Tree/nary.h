#include <iostream>
#include <cmath>

#define OSINT int
#define INF 1e36
#define MIN_TOL 1e-5

using namespace std;

OSINT handle_input(double **, OSINT *, OSINT *, OSINT, OSINT);

double nary_interp(double *, double **, double *, double *, OSINT *, OSINT *, OSINT *, OSINT, OSINT);
void make_tree(double **, double *, OSINT *, OSINT *, OSINT, OSINT, OSINT, OSINT);
double interp_tree(double *, double *, double *, OSINT *, OSINT *, OSINT, OSINT, OSINT, OSINT);
OSINT locate(double, double *, OSINT, OSINT, OSINT);
double distance(double, double *, OSINT);

void get_children(double **, OSINT *, OSINT *, OSINT, OSINT);
OSINT get_NODES(OSINT *); 
OSINT get_LENGTH(OSINT, OSINT);

OSINT get_index(double *, OSINT *, double, OSINT, OSINT, OSINT);
double get_value(double *, OSINT);
OSINT get_num(double *, OSINT, OSINT);
OSINT get_parent_index(double *, OSINT, OSINT);
OSINT get_child_index(double *, OSINT, OSINT, OSINT, OSINT);

void push(OSINT *, OSINT, OSINT);
void push(double *, double, OSINT);
OSINT pop(OSINT *, OSINT);
double pop(double *, OSINT);
OSINT length(double *, OSINT);

void print(OSINT *, OSINT);
void print(double *, OSINT);
