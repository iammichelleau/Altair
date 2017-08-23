#include <iostream>
#include "../../Eigen/Dense"

using namespace std;
using namespace Eigen;

#define OSINT int
#define INF 1e36

int interpolate(double, double, OSINT *, double *, double *, double *, double *, double *, Matrix4f &, Vector4f &, Vector4f &, OSINT);
int simple(double *, double *, double, OSINT *, double *, OSINT);
void smooth(double, double, double *, Matrix4f &, Vector4f &, Vector4f &, double *);
void get_results(double *, double *, double, OSINT *, double*, OSINT);
bool equal(double, double);
bool in_between(double, double, double);
