
#include <iostream>
#include <time.h>
#include <cmath>

using namespace std;

#define OSINT int
#define N 300
#define L (2*N + 1)
#define INF 1e36

void initialization(double *, double *);
int interpolate(double *, double *, double, OSINT *, double *);
bool equal(double, double);
bool in_between(double, double, double);
void get_results(double *, double *, double, OSINT *, double*, OSINT);
void test(double *, double *, double, OSINT *, OSINT);

int main() {
    OSINT i, ext, *index = new OSINT[3];
    double d, *d_array = new double[L], *f_array = new double[L], *results = new double[10];
    srand((unsigned OSINT)time(NULL));
    
    initialization(d_array, f_array);
    
    for(i = 0; i < N; i++){
        double min = -2*M_PI, max = 2*M_PI;
        d = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
        ext = interpolate(d_array, f_array, d, index, results);
        test(results, d_array, d, index, ext);
    } // for i
    
    return 0;
} // main()

void initialization(double *d_array, double *f_array){
    OSINT i = 0, j = 0;
    
    for(j = N; j > 0; j--){
        d_array[i] = -j * 1e-2;
        f_array[i] = sin(d_array[i]);
//        cout << d_array[i] << " " << f_array[i] << endl;
        i++;
    } // for j
    
    for(j = 0; j < (N + 1); j++){
        d_array[i] = j * 1e-2;
        f_array[i] = sin(d_array[i]);
//        cout << d_array[i] << " " << f_array[i] << endl;
        i++;
    } // for i
} // initialization()

int interpolate(double *d_array, double *f_array, double d, OSINT *index, double *results){
    OSINT i, index1, index2, ext;
    
    cout << "Interpolating " << d << "..." << endl;
    
    for(i = 0; i < L; i++){
        if(equal(d, d_array[i])){
            cout << "f(" << d << ") = " << f_array[i] << endl;
            ext = 0;
            index[0] = -1;
            index[1] = -1;
            index[2] = -1;
            return ext;
        } // if
        if(d_array[i] > d){
            i = i - 1;
            break;
        } // if
    } // for i
    
    if(i == -1)
        i += 1;
    if(i == L)
        i -= 2;
    
    index1 = i;
    index2 = i + 1;
    
    cout << "Interpolating between: " << d_array[index1] << " " << d_array[index2] << endl;
    
    if((d < (d_array[index2] + d_array[index1])/2.0) && (index1 != 0)){
        ext = -1;
        index[0] = index1 - 1;
        index[1] = index1;
        index[2] = index2;
        get_results(d_array, f_array, d, index, results, ext);
        return ext;
    } // if
    
    if((d > (d_array[index2] + d_array[index1])/2.0) && (index2 != L - 1)){
        ext = 1;
        index[0] = index1;
        index[1] = index2;
        index[2] = index2 + 1;
        get_results(d_array, f_array, d, index, results, ext);
        return ext;
    } // if
    
    ext = 0;
    index[0] = index1;
    index[1] = index2;
    index[2] = -1;
    get_results(d_array, f_array, d, index, results, ext);
    return ext;
} // interpolate()

bool equal(double a, double b){
    double tol = 1e-10;
    
    if(abs(a - b) < tol)
        return true;
    return false;
} //  equal()

bool in_between(double theo, double interp_1, double interp_2){
    if((interp_1 <= theo && theo <= interp_2) || ((interp_2 <= theo && theo <= interp_1)))
        return true;
    else
        return false;
} // test_increasing()

void get_results(double *d_array, double *f_array, double d, OSINT *index, double *results, OSINT ext){
    double m1 = 0, m2 = 0, f1 = 0, f2 = 0;
    
    m1 = (f_array[index[1]] - f_array[index[0]]) / (d_array[index[1]] - d_array[index[0]]);
    f1 = f_array[index[0]] + m1 * (d - d_array[index[0]]);
    
    results[0] = f1;
    results[1] = -INF;
    results[2] = m1;
    results[4] = f_array[index[0]];
    results[3] = -INF;
    results[5] = f_array[index[1]];
    results[6] = -INF;
    results[7] = d_array[index[0]];
    results[8] = d_array[index[1]];
    results[9] = -INF;
    
    if(ext != 0){
        m2 = (f_array[index[2]] - f_array[index[1]]) / (d_array[index[2]] - d_array[index[1]]);
        f2 = f_array[index[1]] + m2 * (d - d_array[index[1]]);
        
        results[1] = f2;
        results[3] = m2;
        results[6] = f_array[index[2]];
        results[9] = d_array[index[2]];
    } // if
} // get_results()

void test(double *results, double *d_array, double d, OSINT *index, OSINT ext){
    double m1, m2, f1, f2, f_theo, m_theo;

    f1 = results[0];
    f2 = results[1];
    m1 = results[2];
    m2 = results[3];
    
    f_theo = sin(d);
    m_theo = cos(d);
    
    if (ext == 0 && index[0] != -1){
        cout << "Ans (f, df): " << f1 << " " << m1 << endl;
        
        if(index[0] == 0){
            if(d < d_array[0])
                cout << "Test Passed: edge case." << endl;
            else
                cout << "Test Failed: edge case." << endl;
        } // if
        
        if(index[1] == L - 1){
            if(d > d_array[L - 1])
                cout << "Test Passed: edge case." << endl;
            else
                cout << "Test Failed: edge case." << endl;
        } // if
    } // if
    
    if(ext != 0){
        if(ext == -1){
            cout << "Ans (f, df): " << f2 << " " << m2 << endl;
            cout << "Ext (left): " << f1 << " " << m1 << endl;
            cout << "Errors of f: " << abs(f2 - f_theo) << " " << abs(f1 - f_theo) << endl;
            cout << "Errors of df: " << abs(m2 - m_theo) << " " << abs(m1 - m_theo) << endl;
        } // if
        if(ext == 1){
            cout << "Ans (f, df): " << f1 << " " << m1 << endl;
            cout << "Ext (right): " << f2 << " " << m2 << endl;
            cout << "Errors: " << abs(f1 - f_theo) << " " << abs(f2 - f_theo) << endl;
            cout << "Errors of df: " << abs(m1 - m_theo) << " " << abs(m2 - m_theo) << endl;
        } // if
        
        if(in_between(f_theo, f1, f2))
            cout << "Test Passed: f_theo = " << f_theo << " is in (f, f_ext)." << endl;
        else
            cout << "Test Failed: f_theo = " << f_theo << " is not in (f, f_ext)." << endl;
    } // if
    
    cout << endl;
} // test()















