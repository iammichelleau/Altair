#include "qsort.h"

void sort(OSINT *A_orig, OSINT *B_orig, OSINT *A, OSINT *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;
    
    for(i = 0; i < N; i++)
        temp_int[i] = A[i];
    
    quicksort(A, index, istack, N);
    sort_by_index(B, index, temp_int, N);
} // sort()

void sort(double *A_orig, OSINT *B_orig, double *A, OSINT *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;

    for(i = 0; i < N; i++)
        temp_double[i] = A[i];
    
    quicksort(A, index, istack, N);
    sort_by_index(B, index, temp_int, N);
} // sort()

void sort(OSINT *A_orig, double *B_orig, OSINT *A, double *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;

    for(i = 0; i < N; i++)
        temp_int[i] = A[i];
    
    quicksort(A, index, istack, N);
    sort_by_index(B, index, temp_double, N);
} // sort()

void sort(double *A_orig, double *B_orig, double *A, double *B, OSINT *istack, OSINT *index,
          OSINT *temp_int, double *temp_double, OSINT N){
    
    OSINT i;
    
    for(i = 0; i < N; i++)
        temp_double[i] = A[i];
    
    quicksort(A, index, istack, N);
    sort_by_index(B, index, temp_double, N);
} // sort()

void sort_by_index(OSINT *B, OSINT *index, OSINT *temp, OSINT N){
    OSINT i;
    for(i = 0; i < N; i++)
        temp[i] = B[i];
    for(i = 0; i < N; i++)
        B[i] = temp[index[i]];
} // sort_by_index()

void sort_by_index(double *B, OSINT *index, double *temp, OSINT N){
    OSINT i;
    for(i = 0; i < N; i++)
        temp[i] = B[i];
    for(i = 0; i < N; i++)
         B[i] = temp[index[i]];
} // sort_by_index()

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

void quicksort(OSINT *A, OSINT *index, OSINT *istack, OSINT N){
    OSINT i, ind, ir = N - 1, j, k, jstack = -1, l = 0;
    OSINT a;
    
    for(;;){
        if(ir - l < QSORT_M){
            for(j = l + 1; j <= ir; j++){
                a = A[j];
                ind = index[j];
                for(i = j - 1; i >= l; i--){
                    if(A[i] <= a) break;
                    A[i + 1] = A[i];
                    index[i + 1] = index[i];
                } // for i
                A[i + 1] = a;
                index[i + 1] = ind;
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
            swap(index[k], index[l + 1]);
            if(A[l] > A[ir]){
                swap(A[l], A[ir]);
                swap(index[l], index[ir]);
            } // if
            if(A[l + 1] > A[ir]){
                swap(A[l + 1], A[ir]);
                swap(index[l + 1], index[ir]);
            } // if
            if(A[l] > A[l + 1]){
                swap(A[l], A[l + 1]);
                swap(index[l], index[l + 1]);
            } // if
            i = l + 1;
            j = ir;
            a = A[l + 1];
            ind = index[l + 1];
            for(;;){
                do i++; while(A[i] < a); 
                do j--; while(A[j] > a); 
                if(j < i) break; 
                swap(A[i], A[j]);
                swap(index[i], index[j]);
            } // for
            A[l + 1] = A[j]; 
            A[j] = a;
            index[l + 1] = index[j];
            index[j] = ind;
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

void quicksort(double *A, OSINT *index, OSINT *istack, OSINT N){
    OSINT i, ind, ir = N - 1, j, k, jstack = -1, l = 0;
    double a;
    
    for(;;){
        if(ir - l < QSORT_M){
            for(j = l + 1; j <= ir; j++){
                a = A[j];
                ind = index[j];
                for(i = j - 1; i >= l; i--){
                    if(A[i] <= a) break;
                    A[i + 1] = A[i];
                    index[i + 1] = index[i];
                } // for i
                A[i + 1] = a;
                index[i + 1] = ind;
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
            swap(index[k], index[l + 1]);
            if(A[l] > A[ir]){
                swap(A[l], A[ir]);
                swap(index[l], index[ir]);
            } // if
            if(A[l + 1] > A[ir]){
                swap(A[l + 1], A[ir]);
                swap(index[l + 1], index[ir]);
            } // if
            if(A[l] > A[l + 1]){
                swap(A[l], A[l + 1]);
                swap(index[l], index[l + 1]);
            } // if
            i = l + 1;
            j = ir;
            a = A[l + 1];
            ind = index[l + 1];
            for(;;){
                do i++; while(A[i] < a);
                do j--; while(A[j] > a);
                if(j < i) break;
                swap(A[i], A[j]);
                swap(index[i], index[j]);
            } // for
            A[l + 1] = A[j];
            A[j] = a;
            index[l + 1] = index[j];
            index[j] = ind;
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
