#include "interp_driver.h"

int main() {
    OSINT i, ext, *index = new OSINT[3];
    double d, zone, *d_array = new double[L], *f_array = new double[L],
    *results = new double[2], *results_simple = new double[10], *results_smooth = new double[2];
    Matrix4f A;
    Vector4f B, X;
    srand((unsigned OSINT)time(NULL));
    
    for(i = 0; i < 5; i++){
        d = (MAX - MIN) * ((double)rand() / (double)RAND_MAX) + MIN;
        zone = 0.1;
        
        initialization(d_array, f_array);
        ext = interpolate(d, zone, index, d_array, f_array, results, results_simple, results_smooth, A, B, X);
        test(results, results_simple, results_smooth, d_array, d, index, ext);
    } // for i
    
    free(d_array, f_array, results, results_simple, results_smooth);
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

void free(double *d_array, double *f_array, double *results, double *results_simple, double *results_smooth){
    delete []d_array;
    delete []f_array;
    delete []results;
    delete []results_simple;
    delete []results_smooth;
} // free()
