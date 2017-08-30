#include "qsort_driver.h"

int main(){
    OSINT n = 0, N = 1000;
    srand((unsigned OSINT)time(NULL));
    
    OSINT *istack = ivector(1, NSTACK), *index = new OSINT[N];
    OSINT *A_int = new OSINT[N], *B_int = new OSINT[N], *temp_int = new OSINT[N];
    OSINT *A_int_orig = new OSINT[N], *B_int_orig = new OSINT[N];
    double *A_double = new double[N], *B_double = new double[N], *temp_double = new double[N];
    double *A_double_orig = new double[N], *B_double_orig = new double[N];
    
    switch(n){
        case 0:
            cout << endl << "Sorting A(int) and B(int)..." << endl;
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_int_orig, B_int_orig, A_int, B_int, istack, index, temp_int, temp_double, N);
            test_increasing(A_int, N);
            test_order(A_int_orig, A_int, index, N);
            test_order(B_int_orig, B_int, index, N);
        case 1:
            cout << endl << "Sorting A(double) and B(int)..." << endl;
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_double_orig, B_int_orig, A_double, B_int, istack, index, temp_int, temp_double, N);
            test_increasing(A_double, N);
            test_order(A_double_orig, A_double, index, N);
            test_order(B_int_orig, B_int, index, N);
        case 2:
            cout << endl << "Sorting A(int) and B(double)..." << endl;
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_int_orig, B_double_orig, A_int, B_double, istack, index, temp_int, temp_double, N);
            test_increasing(A_int, N);
            test_order(A_int_orig, A_int, index, N);
            test_order(B_double_orig, B_double, index, N);
        case 3:
            cout << endl << "Sorting A(double) and B(double)..." << endl;
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_double_orig, B_double_orig, A_double, B_double, istack, index, temp_int,
                 temp_double, N);
            test_increasing(A_double, N);
            test_order(A_double_orig, A_double, index, N);
            test_order(B_double_orig, B_double, index, N);
    } // switch
    
    free(istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
         A_double, B_double, temp_double, A_double_orig, B_double_orig);
	
    return 0;
} // main()

void initialization(OSINT N, OSINT *istack, OSINT *index, OSINT *A_int, OSINT *B_int, OSINT *temp_int,
                    OSINT *A_int_orig, OSINT *B_int_orig, double *A_double, double *B_double,
                    double *temp_double, double *A_double_orig, double *B_double_orig){
    
    OSINT i;
    
    for(i = 0; i < N; i++){
        index[i] = i;
        temp_int[i] = 0;
        temp_double[i] = 0;
    } // for i
    
    for(i = 0; i < N; i++){
        A_int[i] = rand() % 1000000 + 1;
        B_int[i] = A_int[i] * 2;
        
        double min = 0.0, max = 1000000.0;
        A_double[i] = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
        B_double[i] = A_double[i] * 2;
        
        A_int_orig[i] = A_int[i];
        B_int_orig[i] = B_int[i];
        A_double_orig[i] = A_double[i];
        B_double_orig[i] = B_double[i];
    } // for i
} // initialization()


void print(OSINT *A, OSINT N){
    OSINT i;
    
    for(i = 0; i < N; i++){
        cout << A[i] << " ";
    }
    cout << endl;
} // print()

void print(double *A, OSINT N){
    OSINT i;
    
    for(i = 0; i < N; i++){
        cout << A[i] << " ";
    }
    cout << endl;
} // print()

void test_increasing(OSINT *A, OSINT N){
    OSINT i, prev, curr;
    
    for(i = 1; i < N; i++){
        prev = A[i - 1];
        curr = A[i];
        if(curr < prev){
            cout << "Test Failed: A is not strictly increasing." << endl;
            return;
        } // if
    } // for i
    cout << "Test Passed: A is strictly increasing." << endl;
} // test_increasing()

void test_increasing(double *A, OSINT N){
    OSINT i;
    double prev, curr;
    
    for(i = 1; i < N; i++){
        prev = A[i - 1];
        curr = A[i];
        if(curr < prev){
            cout << "Test Failed: A is not strictly increasing." << endl;
            return;
        } // if
    } // for i
    cout << "Test Passed: A is strictly increasing." << endl;
} // test_increasing()

void test_order(OSINT *orig, OSINT *sorted, OSINT *index, OSINT N){
    OSINT i;
    
    for(i = 0; i < N; i++){
        if(sorted[i] != orig[index[i]]){
            cout << "Test Failed: orig[index] != sorted." << endl;
            return;
        } // if
    } // for i
    cout << "Test Passed: orig[index] = sorted." << endl;
} // test_order()

void test_order(double *orig, double *sorted, OSINT *index, OSINT N){
    OSINT i;
    
    for(i = 0; i < N; i++){
        if(sorted[i] != orig[index[i]]){
            cout << "Test Failed: orig[index] != sorted." << endl;
            return;
        } // if
    } // for i
    cout << "Test Passed: orig[index] = sorted." << endl;
} // test_order()

OSINT *ivector(long nl, long nh){
    OSINT *v;
    
    v=(OSINT *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(OSINT)));
    if (!v) cout << "ERROR: allocation failure in ivector(). " << endl;
    return v-nl+NR_END;
} // ivector()

void free(OSINT *istack, OSINT *index, OSINT *A_int, OSINT *B_int, OSINT *temp_int,
          OSINT *A_int_orig, OSINT *B_int_orig, double *A_double, double *B_double,
          double *temp_double, double *A_double_orig, double *B_double_orig){
    delete []istack;
    delete []index;
    delete []A_int;
    delete []B_int;
    delete []temp_int;
    delete []A_int_orig;
    delete []B_int_orig;
    delete []A_double;
    delete []B_double;
    delete []temp_double;
    delete []A_double_orig;
    delete []B_double_orig;
} // free()

/*
void get_index(OSINT *temp, OSINT *A, OSINT *index, OSINT N){
    OSINT i, j, ind = 0, count, add;
    
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if (temp[i] == A[j]){
                ind = j;
                break;
            } // if
        } // for j
        index[i] = ind;
    } // for i
    
    for(i = 0; i < N; i++){
        ind = index[i];
        count = 0;
        for(j = 0; j < N; j++){
            if(ind == index[j])
                count++;
        } // for j
        if(count > 1){
            add = 0;
            for(j = 0; j < N; j++){
                if(ind == index[j]){
                    index[j] += add;
                    add++;
                } // if
            } // for j
        } // if
    } // for i
} // get_index()

void get_index(double *temp, double *A, OSINT *index, OSINT N){
    OSINT i, j, ind = 0, count, add;
    
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if (temp[i] == A[j]){
                ind = j;
                break;
            } // if
        } // for j
        index[i] = ind;
    } // for i
    
    for(i = 0; i < N; i++){
        ind = index[i];
        count = 0;
        for(j = 0; j < N; j++){
            if(ind == index[j])
                count++;
        } // for j
        if(count > 1){
            add = 0;
            for(j = 0; j < N; j++){
                if(ind == index[j]){
                    index[j] += add;
                    add++;
                } // if
            } // for j
        } // if
    } // for i
} // get_index()
*/
