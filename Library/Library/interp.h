#include <iostream>
#include "../../Eigen/Dense"

using namespace std;
using namespace Eigen;

#define OSINT int
#define N 300
#define L (2*N + 1)
#define INF 1e36

int interpolate(double, double, OSINT *, double *, double *, double *, double *, double *, Matrix4f, Vector4f, Vector4f);
int simple(double *, double *, double, OSINT *, double *);
void smooth(double, double, double *, Matrix4f, Vector4f, Vector4f, double *);
void get_results(double *, double *, double, OSINT *, double*, OSINT);
bool equal(double, double);
bool in_between(double, double, double);
