#include "biinterp.h"

void interpolate(double x, double y, double zone, OSINT *x_ind, OSINT *y_ind, double ***table, OSINT Q, OSINT M, double *results,
                 Matrix4f &A, Vector4f &B, Vector4f &X){
    OSINT ext;
    
    ext = get_points(x, y, x_ind, y_ind, table, Q, M);
    if(ext == 0)
        simple(x, y, x_ind, y_ind, table, Q, M, results);
    else
        smooth(x, y, zone, x_ind, y_ind, table, Q, M, results, A, B, X);
} // interpolate()

void simple(double x, double y, OSINT *x_ind, OSINT *y_ind, double ***table, OSINT Q, OSINT M, double *results){
    double f1, f2, f3, f4, x1, x2, x3, x4, y1, y2, f_xy1, f_xy2, f, dfdx, dfdy, dfdxy;
    
    f1 = table[y_ind[0]][x_ind[0]][0];
    f2 = table[y_ind[0]][x_ind[1]][0];
    f3 = table[y_ind[1]][x_ind[3]][0];
    f4 = table[y_ind[1]][x_ind[4]][0];
    x1 = table[y_ind[0]][x_ind[0]][1];
    x2 = table[y_ind[0]][x_ind[1]][1];
    x3 = table[y_ind[1]][x_ind[3]][1];
    x4 = table[y_ind[1]][x_ind[4]][1];
    y1 = table[y_ind[0]][x_ind[0]][2];
    y2 = table[y_ind[1]][x_ind[0]][2];
    
    f_xy1 = f1 + (x - x1)/(x2 - x1) * (f2 - f1);
    f_xy2 = f4 + (x - x4)/(x3 - x4) * (f3 - f4);
    f = f_xy1 + (y - y1)/(y2 - y1) * (f_xy2 - f_xy1);
    
    //    cout << "df(x, y1): " << (f2 - f1)/(x2 - x1) << endl;
    //    cout << "df(x, y2): " << (f3 - f4)/(x3 - x4) << endl;
    
    dfdx = (f2 - f1)/(x2 - x1) + (f3 - f4)/(x3 - x4) * (y - y1)/(y2 - y1) - (f2 - f1)/(x2 - x1) * (y - y1)/(y2 - y1);
    dfdy = (f_xy2 - f_xy1)/(y2 - y1);
    dfdxy = ((f3 - f4)/(x3 - x4) - (f2 - f1)/(x2 - x1))/(y2 - y1);
    
    results[0] = f;
    results[1] = dfdx;
    results[2] = dfdy;
    results[3] = dfdxy;
} // simple()

void smooth(double x, double y, double zone, OSINT *x_ind, OSINT *y_ind, double ***table, OSINT Q, OSINT M, double *results,
            Matrix4f &A, Vector4f &B, Vector4f &X){
    OSINT i;
    double f1, f2, f3, x1, x2, x3, y1, y2, a, b, f_a, f_b, df_a, df_b,
    f_xy1 = 0, f_xy2 = 0, df_xy1 = 0, df_xy2 = 0, f, dfdx, dfdy, dfdxy;
    
    y1 = table[y_ind[0]][0][2];
    y2 = table[y_ind[1]][0][2];
    
    for(i = 0; i < 2; i++){
        f1 = table[y_ind[i]][x_ind[i * 3]][0];
        f2 = table[y_ind[i]][x_ind[i * 3 + 1]][0];
        f3 = table[y_ind[i]][x_ind[i * 3 + 2]][0];
        x1 = table[y_ind[i]][x_ind[i * 3]][1];
        x2 = table[y_ind[i]][x_ind[i * 3 + 1]][1];
        x3 = table[y_ind[i]][x_ind[i * 3 + 2]][1];
        
        a = x1 + (1 - zone) * (x2 - x1);
        b = x2 + zone * (x3 - x2);
        
        df_a = (f2 - f1)/(x2 - x1);
        df_b = (f3 - f2)/(x3 - x2);
        f_a = f1 + df_a * (a - x1);
        f_b = f2 + df_b * (b - x2);
        
        if(in_between(x, a, b)){
            A << pow(a, 3), pow(a, 2), a, 1, pow(b, 3), pow(b, 2), b, 1, 3*pow(a, 2), 2*a, 1, 0, 3*pow(b, 2), 2*b, 1, 0;
            B << f_a, f_b, df_a, df_b;
            X = A.colPivHouseholderQr().solve(B);
            
            if(i == 0){
                f_xy1 = X[0] * pow(x, 3) + X[1] * pow(x, 2) + X[2] * x + X[3];
                df_xy1 = 3 * X[0] * pow(x, 2) + 2 * X[1] * x + X[2];
            } // if
            if(i == 1){
                f_xy2 = X[0] * pow(x, 3) + X[1] * pow(x, 2) + X[2] * x + X[3];
                df_xy2 = 3 * X[0] * pow(x, 2) + 2 * X[1] * x + X[2];
            } // if
        } // if
        else{
            if(i == 0){
                if(in_between(x, x1, x2)){
                    f_xy1 = f1 + (x - x1)/(x2 - x1) * (f2 - f1);
                    df_xy1 = (f2 - f1)/(x2 - x1);
                } // if
                if(in_between(x, x2, x3)){
                    f_xy1 = f2 + (x - x2)/(x3 - x2) * (f3 - f2);
                    df_xy1 = (f3 - f2)/(x3 - x2);
                } // if
            } // if
            if(i == 1){
                if(in_between(x, x1, x2)){
                    f_xy2 = f1 + (x - x1)/(x2 - x1) * (f2 - f1);
                    df_xy2 = (f2 - f1)/(x2 - x1);
                } //  if
                if(in_between(x, x2, x3)){
                    f_xy2 = f2 + (x - x2)/(x3 - x2) * (f3 - f2);
                    df_xy2 = (f3 - f2)/(x3 - x2);
                } // if
            } // if
        } // else
    } // for i
    
    f = f_xy1 + (y - y1)/(y2 - y1) * (f_xy2 - f_xy1);
    dfdx = df_xy1 + (y - y1)/(y2 - y1) * (df_xy2 - df_xy1);
    dfdy = (f_xy2 - f_xy1)/(y2 - y1);
    dfdxy = (df_xy2 - df_xy1)/(y2 - y1);
    
    results[0] = f;
    results[1] = dfdx;
    results[2] = dfdy;
    results[3] = dfdxy;
} // smooth()

int get_points(double x, double y, OSINT *x_ind, OSINT *y_ind, double ***table, OSINT Q, OSINT M){
    OSINT ext0, ext1;
    
    get_y_ind(y, y_ind, table, Q, M);
    ext0 = get_x_ind(0, x, y_ind[0], x_ind, table, Q, M);
    ext1 = get_x_ind(1, x, y_ind[1], x_ind, table, Q, M);
    
    if(ext0 == 0 && ext1 == 0)
        return 0;
    else
        return 1;
} // get_points()

void get_y_ind(double y, OSINT *y_ind, double ***table, OSINT Q, OSINT M){
    OSINT i, y1, y2;
    
    for(i = 0; i < Q; i++){
        if(table[i][0][2] > y){
            i = i - 1;
            break;
        } // if
    } // for i
    
    if(i == -1)
        i += 1;
    if(i == Q)
        i -= 2;
    
    y1 = i;
    y2 = i + 1;
    
    y_ind[0] = y1;
    y_ind[1] = y2;
} // get_y_ind()

int get_x_ind(OSINT flag, double x, OSINT y_ind, OSINT *x_ind, double ***table, OSINT Q, OSINT M){
    OSINT i, x1, x2, ext;
    double x_avg;
    
    for(i = 0; i < M; i++){
        if(table[y_ind][i][1] > x){
            i = i - 1;
            break;
        } // if
        if(table[y_ind][i][1] == -INF){
            i = i - 2;
            break;
        } // if
    } // for i
    
    if(i == -1)
        i += 1;
    if(i == M)
        i -= 2;
    
    x1 = i;
    x2 = i + 1;
    
    x_avg = (table[y_ind][x2][1] + table[y_ind][x1][1])/2.0;
    
    if(in_between(x, table[y_ind][x1][1], x_avg) && (x1 != 0)){
        ext = -1;
        x_ind[flag * 3] = x1 - 1;
        x_ind[flag * 3 + 1] = x1;
        x_ind[flag * 3 + 2] = x2;
        return ext;
    } // if
    
    if(in_between(x, x_avg, table[y_ind][x2][1]) && (x2 != M - 1)){
        ext = 1;
        x_ind[flag * 3] = x1;
        x_ind[flag * 3 + 1] = x2;
        x_ind[flag * 3 + 2] = x2 + 1;
        return ext;
    } // if
    
    ext = 0;
    x_ind[flag * 3] = x1;
    x_ind[flag * 3 + 1] = x2;
    x_ind[flag * 3 + 2] = -1;
    return ext;
} // get_x_ind()

bool in_between(double x, double a, double b){
    if((a < x && x < b) || ((b < x && x < a)))
        return true;
    else
        return false;
} // in_between()
