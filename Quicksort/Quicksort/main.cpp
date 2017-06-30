#include "header.h"

int main(){
    OSINT n = 0, N = 10000;
    srand((unsigned OSINT)time(NULL));
    
    OSINT *istack = ivector(1, NSTACK), *index = new OSINT[N];
    OSINT *A_int = new OSINT[N], *B_int = new OSINT[N], *temp_int = new OSINT[N];
    OSINT *A_int_orig = new OSINT[N], *B_int_orig = new OSINT[N];
    double *A_double = new double[N], *B_double = new double[N], *temp_double = new double[N];
    double *A_double_orig = new double[N], *B_double_orig = new double[N];
    
    switch(n){
        case 0:
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_int_orig, B_int_orig, A_int, B_int, istack, index, temp_int, temp_double, N);
        case 1:
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_double_orig, B_int_orig, A_double, B_int, istack, index, temp_int, temp_double, N);
        case 2:
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_int_orig, B_double_orig, A_int, B_double, istack, index, temp_int, temp_double, N);
        case 3:
            initialization(N, istack, index, A_int, B_int, temp_int, A_int_orig, B_int_orig,
                           A_double, B_double, temp_double, A_double_orig, B_double_orig);
            sort(A_double_orig, B_double_orig, A_double, B_double, istack, index, temp_int,
                     temp_double, N);
    } // switch
    return 0;
} // main()

void initialization(OSINT N, OSINT *istack, OSINT *index, OSINT *A_int, OSINT *B_int, OSINT *temp_int,
                    OSINT *A_int_orig, OSINT *B_int_orig, double *A_double, double *B_double,
                    double *temp_double, double *A_double_orig, double *B_double_orig){
    
    OSINT i;
    
    for(i = 0; i < N; i++){
        index[i] = 0; 
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

void sort(OSINT *A_orig, OSINT *B_orig, OSINT *A, OSINT *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;
    
    cout << endl << "Sorting A(int), B(int)..." << endl;
    
    for(i = 0; i < N; i++)
        temp_int[i] = A[i];
    
    quicksort(A, istack, N);
    get_index(temp_int, A, index, N);
    sort_by_index(B, index, temp_int, N);
    
    test_increasing(A, N);
    test_order(A_orig, A, index, N);
    test_order(B_orig, B, index, N);
} // sort()

void sort(double *A_orig, OSINT *B_orig, double *A, OSINT *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;
    
    cout << endl << "Sorting A(double), B(int)..." << endl;

    for(i = 0; i < N; i++)
        temp_double[i] = A[i];
    
    quicksort(A, istack, N);
    get_index(temp_double, A, index, N);
    sort_by_index(B, index, temp_int, N);
    
    test_increasing(A, N);
    test_order(A_orig, A, index, N);
    test_order(B_orig, B, index, N);
} // sort()

void sort(OSINT *A_orig, double *B_orig, OSINT *A, double *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;
    
    cout << endl << "Sorting A(int), B(double)..." << endl;

    for(i = 0; i < N; i++)
        temp_int[i] = A[i];
    
    quicksort(A, istack, N);
    get_index(temp_int, A, index, N);
    sort_by_index(B, index, temp_double, N);
    
    test_increasing(A, N);
    test_order(A_orig, A, index, N);
    test_order(B_orig, B, index, N);
} // sort()

void sort(double *A_orig, double *B_orig, double *A, double *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;
    
    cout << endl << "Sorting A(double), B(double)..." << endl;
    
    for(i = 0; i < N; i++)
        temp_double[i] = A[i];
    
    quicksort(A, istack, N);
    get_index(temp_double, A, index, N);
    sort_by_index(B, index, temp_double, N);
    
    test_increasing(A, N);
    test_order(A_orig, A, index, N);
    test_order(B_orig, B, index, N);
} // sort()

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

void sort_by_index(OSINT *B, OSINT *index, OSINT *temp, OSINT N){
    OSINT i;
    for(i = 0; i < N; i++)
        temp[i] = B[i];
    for(i = 0; i < N; i++)
        B[index[i]] = temp[i];
} // sort_by_index()

void sort_by_index(double *B, OSINT *index, double *temp, OSINT N){
    OSINT i;
    for(i = 0; i < N; i++)
        temp[i] = B[i];
    for(i = 0; i < N; i++)
        B[index[i]] = temp[i];
} // sort_by_index()

OSINT *ivector(long nl, long nh){
    OSINT *v;
    
    v=(OSINT *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(OSINT)));
    if (!v) cout << "ERROR: allocation failure in ivector(). " << endl;
    return v-nl+NR_END;
} // ivector()

void swap(OSINT &a, OSINT &b){
    OSINT temp = a;
    a = b;
    b = temp;
} // swap()

void swap(double &a, double &b){
    double temp = a;
    a = b;
    b = temp;
} // swap()

void quicksort(OSINT *A, OSINT *istack, OSINT N){
    OSINT i, ir = N - 1, j, k, jstack = -1, l = 0;
    OSINT a;
    
    for(;;){
        if(ir - l < M){
            for(j = l + 1; j <= ir; j++){
                a = A[j];
                for(i = j - 1; i >= l; i--){
                    if(A[i] <= a) break;
                    A[i + 1] = A[i];
                } // for i
                A[i + 1] = a;
            } // for j
            if(jstack == 0) break;
            ir = istack[jstack--];
            l = istack[jstack--];
        } // if
        else{
            k = (l + ir) >> 1;
            if(abs(k) >= N)
                return;
            swap(A[k], A[l + 1]);
            if(A[l] > A[ir]){
                swap(A[l], A[ir]);
            } // if
            if(A[l + 1] > A[ir]){
                swap(A[l + 1], A[ir]);
            } // if
            if(A[l] > A[l + 1]){
                swap(A[l], A[l + 1]);
            } // if
            i = l + 1;
            j = ir;
            a = A[l + 1];
            for(;;){
                do i++; while(A[i] < a); 
                do j--; while(A[j] > a); 
                if(j < i) break; 
                swap(A[i], A[j]); 
            } // for
            A[l + 1] = A[j]; 
            A[j] = a;
            jstack += 2; 
            
            if(jstack > NSTACK) cout << "ERROR: NSTACK too small in sort." << endl; 
            if(ir - i + 1 >= j - 1){
                istack[jstack] = ir; 
                istack[jstack - 1] = i; 
                ir = j - 1; 
            }
            else{
                istack[jstack] = j - 1; 
                istack[jstack - 1] = l; 
                l = i; 
            } // else
        } // else
    } // for
} // quicksort()

void quicksort(double *A, OSINT *istack, OSINT N){
    OSINT i, ir = N - 1, j, k, jstack = -1, l = 0;
    double a;
    
    for(;;){
        if(ir - l < M){
            for(j = l + 1; j <= ir; j++){
                a = A[j];
                for(i = j - 1; i >= l; i--){
                    if(A[i] <= a) break;
                    A[i + 1] = A[i];
                } // for i
                A[i + 1] = a;
            } // for j
            if(jstack == 0) break;
            ir = istack[jstack--];
            l = istack[jstack--];
        } // if
        else{
            k = (l + ir) >> 1;
            if(abs(k) >= N)
                return;
            swap(A[k], A[l + 1]);
            if(A[l] > A[ir]){
                swap(A[l], A[ir]);
            } // if
            if(A[l + 1] > A[ir]){
                swap(A[l + 1], A[ir]);
            } // if
            if(A[l] > A[l + 1]){
                swap(A[l], A[l + 1]);
            } // if
            i = l + 1;
            j = ir;
            a = A[l + 1];
            for(;;){
                do i++; while(A[i] < a);
                do j--; while(A[j] > a);
                if(j < i) break;
                swap(A[i], A[j]);
            } // for
            A[l + 1] = A[j];
            A[j] = a;
            jstack += 2;
            
            if(jstack > NSTACK) cout << "ERROR: NSTACK too small in sort." << endl;
            if(ir - i + 1 >= j - 1){
                istack[jstack] = ir;
                istack[jstack - 1] = i;
                ir = j - 1;
            }
            else{
                istack[jstack] = j - 1;
                istack[jstack - 1] = l;
                l = i;
            } // else
        } // else
    } // for
} // quicksort()

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
        if(orig[i] != sorted[index[i]]){
            cout << "Test Failed: orig[index] != sorted." << endl;
            return;
        } // if
    } // for i
    cout << "Test Passed: orig[index] = sorted." << endl;
} // test_order()

void test_order(double *orig, double *sorted, OSINT *index, OSINT N){
    OSINT i;
    
    for(i = 0; i < N; i++){
        if(orig[i] != sorted[index[i]]){
            cout << "Test Failed: orig[index] != sorted." << endl;
            return;
        } // if
    } // for i
    cout << "Test Passed: orig[index] = sorted." << endl;
} // test_order()














