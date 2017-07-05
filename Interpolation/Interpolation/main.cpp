#include "header.h"

int main() {
    OSINT i, *index = new OSINT[3];
    double d, zone, *d_array = new double[L], *f_array = new double[L],
        *results = new double[2], *results_simple = new double[10], *results_smooth = new double[2];
    Matrix4f A;
    Vector4f B, X;
    srand((unsigned OSINT)time(NULL));
    
    for(i = 0; i < N; i++){
        d = (MAX - MIN) * ((double)rand() / (double)RAND_MAX) + MIN;
        zone = 0.1;
    
        initialization(d_array, f_array);
        interpolate(d, zone, index, d_array, f_array, results, results_simple, results_smooth, A, B, X);
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

bool equal(double a, double b){
    double tol = 1e-10;
    
    if(abs(a - b) < tol)
        return true;
    return false;
} //  equal()

bool in_between(double theo, double interp_1, double interp_2){
    if((interp_1 < theo && theo < interp_2) || ((interp_2 < theo && theo < interp_1)))
        return true;
    else
        return false;
} // in_between()

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

void interpolate(double d, double zone, OSINT *index, double *d_array, double *f_array,
                 double *results, double *results_simple, double *results_smooth,
                 Matrix4f A, Vector4f B, Vector4f X){
    OSINT ext;
    double d1, d2, d3, a, b;
    
    d1 = results_simple[7];
    d2 = results_simple[8];
    d3 = results_simple[9];
    
    a = d1 + (1 - zone) * (d2 - d1);
    b = d2 + zone * (d3 - d2);

    ext = simple(d_array, f_array, d, index, results_simple);
    if(in_between(d, d_array[index[0]], d_array[index[1]]) || index[2] == -1){
        results[0] = results_simple[0];
        results[1] = results_simple[2];
    } // if
    if(in_between(d, d_array[index[1]], d_array[index[2]]) && index[2] != -1){
        results[0] = results_simple[1];
        results[1] = results_simple[3];
    } // if
    
    if(ext != 0 && in_between(d, a, b)){
        smooth(d, zone, results_simple, A, B, X, results_smooth);
        results[0] = results_smooth[0];
        results[1] = results_smooth[1];
    } // if
    
    test(results, results_simple, results_smooth, d_array, d, index, ext);
} // interpolate()

int simple(double *d_array, double *f_array, double d, OSINT *index, double *results){
    OSINT i, index1, index2, ext;
    double d_avg;
    
    cout << "Interpolating " << d << "..." << endl;
    
    for(i = 0; i < L; i++){
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
    d_avg = (d_array[index2] + d_array[index1])/2.0;
    
    if(in_between(d, d_array[index1], d_avg) && (index1 != 0)){
        ext = -1;
        index[0] = index1 - 1;
        index[1] = index1;
        index[2] = index2;
        get_results(d_array, f_array, d, index, results, ext);
        return ext;
    } // if
    
    if(in_between(d, d_avg, d_array[index2]) && (index2 != L - 1)){
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
} // simple()

void smooth(double d, double zone, double *results_simple, Matrix4f A, Vector4f B, Vector4f X,
            double *results_smooth){
    double f1, f2, f3, d1, d2, d3;
    double a, b, m_a, m_b, f_a, f_b;
    
    f1 = results_simple[4];
    f2 = results_simple[5];
    f3 = results_simple[6];
    d1 = results_simple[7];
    d2 = results_simple[8];
    d3 = results_simple[9];
    
    a = d1 + (1 - zone) * (d2 - d1);
    m_a = (f2 - f1) / (d2 - d1);
    f_a = f1 + m_a * (a - d1);
    
    b = d2 + zone * (d3 - d2);
    m_b = (f3 - f2) / (d3 - d2);
    f_b = f2 + m_b * (b - d2);
    
    A << pow(a, 3), pow(a, 2), a, 1, pow(b, 3), pow(b, 2), b, 1, 3*pow(a, 2), 2*a, 1, 0, 3*pow(b, 2), 2*b, 1, 0;
    B << f_a, f_b, m_a, m_b;
    X = A.colPivHouseholderQr().solve(B);
    
    results_smooth[0] = X[0] * pow(d, 3) + X[1] * pow(d, 2) + X[2] * d + X[3];
    results_smooth[1] = 3 * X[0] * pow(d, 2) + 2 * X[1] * d + X[2];
} // smooth()

void test(double *results, double *results_simple, double *results_smooth,
          double *d_array, double d, OSINT *index, OSINT ext){
    double m1, m2, m_smooth, f1, f2, f_smooth, f_theo, m_theo;
    double f, m;
    
    f = results[0];
    m = results[1];

    f1 = results_simple[0];
    f2 = results_simple[1];
    f_smooth = results_smooth[0];
    m1 = results_simple[2];
    m2 = results_simple[3];
    m_smooth = results_smooth[1];
    
    f_theo = sin(d);
    m_theo = cos(d);
    
    cout << "Results (f, df): " << f << " " << m << endl;
    
    if (ext == 0){
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
    
    if (ext != 0)
        cout << "Errors (f, df): " << abs(f - f_theo) << " " << abs(m - m_theo) << endl;
    
    cout << endl;
} // test()

























