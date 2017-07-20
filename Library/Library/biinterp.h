#include <iostream>
#include "../../Eigen/Dense"

using namespace std;
using namespace Eigen;

#define OSINT int
#define INF 1e36

void interpolate(double, double, double, OSINT *, OSINT *, double ***, OSINT, OSINT, double *, Matrix4f &, Vector4f &, Vector4f &);
void simple(double, double, OSINT *, OSINT *, double ***, OSINT, OSINT, double *);
void smooth(double, double, double, OSINT *, OSINT *, double ***, OSINT, OSINT, double *, Matrix4f &, Vector4f &, Vector4f &);
int get_points(double, double, OSINT *, OSINT *, double ***, OSINT, OSINT);
int get_x_ind(OSINT, double, OSINT, OSINT *, double ***, OSINT, OSINT);
void get_y_ind(double, OSINT *, double ***, OSINT, OSINT);
bool in_between(double, double, double);
