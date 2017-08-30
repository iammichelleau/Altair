#include "bicubic.h"

void uniform_grid(double *x_array, double *d_array, double *f_array, 
	OSINT *interp_index, double *interp_results, double ****data, double ***raw_data, 
	OSINT X, OSINT MAX_X, OSINT Y){

	make_grid(x_array, raw_data, data, X, MAX_X, Y);
	interp_grid(data, X, Y, interp_index, d_array, f_array, interp_results);
} // uniform_grid()

void make_grid(double *x_array, double ***raw_data, double ****data, OSINT X, OSINT MAX_X, OSINT Y){
    OSINT i, j, k;
    
    for(j = 0; j < Y; j++){
        for(i = 0; i < X; i++){
            (*data)[j][i][0] = -INF;
            (*data)[j][i][1] = x_array[i];
            (*data)[j][i][2] = raw_data[j][0][2];
            
            for(k = 0; k < MAX_X; k++){
                if(x_array[i] == raw_data[j][k][1])
                    (*data)[j][i][0] = raw_data[j][k][0];
            } // for k
        } // for j
    } // for i
} // make_grid()

void interp_grid(double ****data, OSINT X, OSINT Y,
                 OSINT *interp_index, double *d_array, double *f_array, double *results){
    OSINT i, j, k, L;
    double d, zone;
    
    for(j = 0; j < Y; j++){
        for(i = 0; i < X; i++){
            if((*data)[j][i][0] == -INF){
                d = (*data)[j][i][1];
                zone = 0.1;

                L = 0;
                for(k = 0; k < X; k++){
                    if((*data)[j][k][0] != -INF){
                        d_array[L] = (*data)[j][k][1];
                        f_array[L] = (*data)[j][k][0];
                        L++;
                    } // if
                } // for k
                
				simple(d_array, f_array, d, interp_index, results, L);
                
                (*data)[j][i][0] = results[0];
            } // if
        } // for i
    } // for j
} // interp_grid()

OSINT simple(double *d_array, double *f_array, double d, OSINT *index, double *results, OSINT L){
    OSINT i, index1, index2, ext;
    double d_avg;
    
//    cout << "Interpolating " << d << "..." << endl;
    
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
    
//    cout <<  "Interpolating between: " << d_array[index1] << " " << d_array[index2] << endl;
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

void bicubic_interp(double x, double y, OSINT *x_ind, OSINT *y_ind,
                    OSINT *bcucof_wt, double *bcucof_x, double *bcucof_cl, double *f, double *f1, double *f2, double *f12,
                    double ***C, double ***data, OSINT X, OSINT Y, double *results){
    
    double d1, d2;
    
    locate(x, y, x_ind, y_ind, data, X, Y);
    derivatives(x, y, x_ind, y_ind, data, X, Y, f, f1, f2, f12);
    
    d1 = data[0][1][1] - data[0][0][1];
    d2 = data[1][0][2] - data[0][0][2];
    bcucof(bcucof_wt, bcucof_x, bcucof_cl, f, f1, f2, f12, d1, d2, C);
    bcuint(x, y, x_ind, y_ind, data, (*C), results);
} // bicubic_interp()

void locate(double x, double y, OSINT *x_ind, OSINT *y_ind, double ***data, OSINT X, OSINT Y){
    OSINT i;
    
    for(i = 0; i < X; i++){
        if(data[0][i][1] > x){
            i = i - 1;
            break;
        } // if
    } // for i
    
    if(i <= 0)
        i = 1;
    if(i >= (X - 2))
        i = X - 3;
    
    x_ind[0] = i;
    x_ind[1] = i + 1;
    
    for(i = 0; i < Y; i++){
        if(data[i][0][2] > y){
            i = i - 1;
            break;
        } // if
    } // for i
    
    if(i <= 0)
        i = 1;
    if(i >= (Y - 2))
        i = Y - 3;
    
    y_ind[0] = i;
    y_ind[1] = i + 1;
    
//    cout << y_ind[0] << " " << y_ind[1] << endl;
} // locate()

void derivatives(double x, double y, OSINT *x_ind, OSINT *y_ind, double ***data, OSINT X, OSINT Y, double *res_f, double *res_f1, double *res_f2, double *res_f12){
    
    OSINT i, j, ind;
    double f, f_xl, f_xu, f_yl, f_yu, xl, xu, yl, yu;
    
    for(j = 0; j < 2; j++){
        for(i = 0; i < 2; i++){
            if(j == 0 && i == 0)
                ind = 0;
            if(j == 0 && i == 1)
                ind = 3;
            if(j == 1 && i == 0)
                ind = 1;
            if(j == 1 && i == 1)
                ind = 2;
            
            f = data[y_ind[j]][x_ind[i]][0];
            f_xl = data[y_ind[j]][x_ind[i] - 1][0];
            f_xu = data[y_ind[j]][x_ind[i] + 1][0];
            f_yl = data[y_ind[j] - 1][x_ind[i]][0];
            f_yu = data[y_ind[j] + 1][x_ind[i]][0];
            xl = data[y_ind[j]][x_ind[i] - 1][1];
            xu = data[y_ind[j]][x_ind[i] + 1][1];
            yl = data[y_ind[j] - 1][x_ind[i]][2];
            yu = data[y_ind[j] + 1][x_ind[i]][2];
            
            res_f[ind] = f;
            res_f1[ind] = (f_xu - f_xl)/(xu - xl);
            res_f2[ind] = (f_yu - f_yl)/(yu - yl);
            res_f12[ind] = (data[y_ind[j] + 1][x_ind[i] + 1][0] - data[y_ind[j] - 1][x_ind[i] + 1][0] - data[y_ind[j] + 1][x_ind[i] - 1][0] + data[y_ind[j] - 1][x_ind[i] - 1][0])/((xu - xl) * (yu - yl));
            
            x = data[y_ind[j]][x_ind[i]][1];
            y = data[y_ind[j]][x_ind[i]][2];
            
//            cout << res_f[ind] << " " << res_f1[ind] << " " << res_f2[ind] << " " << res_f12[ind] << endl;
//            cout << x+y << " " << 1 << " " << 1 << " " << 0 << endl << endl;
        } // for i
    } // for j
} // derivatives()

void bcucof(OSINT *wt, double *x, double *cl, double *y, double *y1, double *y2, double *y12, double d1, double d2, double ***c){
    OSINT i, j, k, l;
    double d1d2, xx;
    
    d1d2 = d1 * d2;
    
    for(i = 0; i < 4; i++){
        x[i] = y[i];
        x[i + 4] = y1[i] * d1;
        x[i + 8] = y2[i] * d2;
        x[i + 12] = y12[i] * d1d2;
    } // for i
    
    for(i = 0; i < 16; i++){
        xx = 0;
        for(k = 0; k < 16; k++)
            xx += wt[i * 16 + k] * x[k];
        cl[i] = xx;
    } // for i
    
    l=0;
    for(i = 0; i < 4; i++){
        for (j = 0; j < 4; j++)
            (*c)[i][j] = cl[l++];
    } // for i
} // bcucof()

void bcuint(double x, double y, OSINT *x_ind, OSINT *y_ind, double ***data, double **C, double *results){
    OSINT i, j;
    double t, u, xi, xip, yj, yjp, r1 = 0, r2 = 0, r3 = 0, r4 = 0;
    
    xi = data[0][x_ind[0]][1];
    xip = data[0][x_ind[1]][1];
    yj = data[y_ind[0]][0][2];
    yjp = data[y_ind[1]][0][2];
    
    t = (x - xi)/(xip - xi);
    u = (y - yj)/(yjp - yj);
    
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            r1 += C[i][j] * pow(t, i) * pow(u, j);
            r2 += i * C[i][j] * pow(t, i - 1) * pow(u, j) / (xip - xi);
            r3 += j * C[i][j] * pow(t, i) * pow(u, j - 1) / (yjp - yj);
            r4 += i * j * C[i][j] * pow(t, i - 1) * pow(u, j - 1) / (xip - xi) / (yjp - yj);
        } // for j
    } // for i
    
    results[0] = r1;
    results[1] = r2;
    results[2] = r3;
    results[3] = r4;
} // bcuint()

OSINT handle_input(double *x_array, OSINT *index, OSINT *istack, OSINT X){
    OSINT i, j;

	quicksort(x_array, index, istack, X);
    
    j = 0;
    for (i = 1; i < X; i++){
        if (x_array[i] != x_array[j]){
            j++;
            x_array[j] = x_array[i];
        } // if
    } //  if
    
    return (j + 1);
} // handle_input()
