#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>
#include "Eigen/Dense"

using namespace std;
using namespace Eigen;

#define OSINT int
#define N 100
#define XMIN -4
#define XMAX 4
#define YMIN -1
#define YMAX 1
#define INF 1e36
OSINT Q = 1;
OSINT M = 1;

void read_input(double ****);
void get_dimensions();
void get_values(double ****);
vector<string> split(const string &, char);
void allocate(double ****);
void de_allocate(double ****);
void interpolate(double, double, double, OSINT *, OSINT *, double ***, double *, Matrix4f, Vector4f, Vector4f);
void simple(double, double, OSINT *, OSINT *, double ***, double *);
void smooth(double, double, double, OSINT *, OSINT *, double ***, double *, Matrix4f, Vector4f, Vector4f);
int get_points(double, double, OSINT *, OSINT *, double ***);
int get_x_ind(OSINT, double, OSINT, OSINT *, double ***);
void get_y_ind(double, OSINT *, double ***);
bool in_between(double, double, double);
void test(double, double, OSINT *, OSINT *, double ***, double *);




