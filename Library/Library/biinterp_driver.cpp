#include "biinterp_driver.h"

OSINT Q = 1;
OSINT M = 1;

OSINT main(){
    OSINT i, *x_ind = new OSINT[6], *y_ind = new OSINT[2];
    double x, y, zone, *results = new double[4], ***table = nullptr;
    Matrix4f A;
    Vector4f B, X;
    string filename = "../../Input/biinterp1.txt";
    srand((unsigned OSINT)time(NULL));
    
    read_input(filename, &table);
    
    for(i = 0; i < N; i++){
        x = (XMAX - XMIN) * ((double)rand() / (double)RAND_MAX) + XMIN;
        y = (YMAX - YMIN) * ((double)rand() / (double)RAND_MAX) + YMIN;
        zone = 0.1;
        cout << "Interpolating point (x, y) = (" << x << ", " << y << ")." << endl;
        interpolate(x, y, zone, x_ind, y_ind, table, Q, M, results, A, B, X);
        test(x, y, x_ind, y_ind, table, results);
    } // for i
    
    free(&table);

    return 0;
} // main()

void read_input(string filename, double ****table){
    get_dimensions(filename);
    
    initialization(table);
    get_values(filename, table);
} // read_input()

void get_dimensions(string filename){
    OSINT n = 1;
    string y, line;
    vector<string> items;
    vector<string>::iterator it;
    
    ifstream file(filename);
    
    if (file.is_open()){
        getline(file,line);
        items = split(line, ' ');
        y = *(items.end() - 1);
        
        while(getline(file,line)){
            items = split(line, ' ');
            n++;
            
            if(y != *(items.end() - 1)){
                y = *(items.end() - 1);
                Q++;
                n = 1;
            } // if
            if(n > M)
                M = n;
        } // while()
        file.close();
    } // if()
    
    else
        cout << "Unable to open file.";
} // get_dimensions()

void get_values(string filename, double ****table){
    OSINT i = 0, j = 0, k = 0;
    string y, line;
    vector<string> items;
    vector<string>::iterator it;
    
    ifstream file(filename);
    
    if (file.is_open()){
        getline(file,line);
        items = split(line, ' ');
        y = *(items.end() - 1);
        
        for(k = 0; k < 3; k++)
            (*table)[i][j][k] = stod(items[k]);
        j++;
        
        while(getline(file,line)){
            items = split(line, ' ');
            
            if(y != *(items.end() - 1)){
                y = *(items.end() - 1);
                i++;
                j = 0;
            } // if
            
            for(k = 0; k < 3; k++)
                (*table)[i][j][k] = stod(items[k]);
            j++;
        } // while()
        file.close();
    } // if()
    
    else
        cout << "Unable to open file.";
} // get_values()

template<typename Out>
void split(const string &s, char delim, Out result){
    string item;
    stringstream ss;
    ss.str(s);
    while(getline(ss, item, delim)) {
        *(result++) = item;
    } // while()
} // split()

vector<string> split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
} // split()

void initialization(double ****table){
    OSINT i, j, k;
    
    *table = new double**[Q];
    for(i = 0; i < Q; i++){
        (*table)[i] = new double*[M];
        for(j = 0; j < M; j++)
            (*table)[i][j] = new double[3];
    } // for i
    
    for(i = 0; i < Q; i++){
        for(j = 0; j < M; j++){
            for(k = 0; k < 3; k++)
                (*table)[i][j][k] = -INF;
        }
    }
} // allocate()

void free(double ****table){
    OSINT i, j;
    
    for(i = 0; i < Q; i++){
        for(j = 0; j < M; j++)
            delete [] (*table)[i][j];
        delete [] (*table)[i];
    } // for i
    delete [] (*table);
} // de_allocate()

void test(double x, double y, OSINT *x_ind, OSINT *y_ind, double ***table, double *results){
    OSINT i, j;
    double x_min = 0, x_max = 0, y_min = 0, y_max = 0;
    double theo_f, theo_dfdx, theo_dfdy, theo_dfdxy;
    
    y_min = table[0][0][2];
    y_max = table[Q-1][0][2];
    
    theo_f = sin(x) * sin(y);
    theo_dfdx = cos(x) * sin(y);
    theo_dfdy = sin(x) * cos(y);
    theo_dfdxy = cos(x) * cos(y);
    
    for(i = 0; i < Q; i++){
        for(j = 0; j < M; j++){
            if(table[i][j][1] > x_max)
                x_max = table[i][j][1];
            if(table[i][j][1] < x_min)
                x_min = table[i][j][1];
        } // for j
    } // for i
    
    cout << "Results: (experimental theoretical error)" << endl;
    cout << "f: " << results[0] << " " << theo_f << " " << abs(results[0] - theo_f) << endl;
    cout << "df/dx: " << results[1] << " " << theo_dfdx << " " << abs(results[1] - theo_dfdx) << endl;
    cout << "df/dy: " << results[2] << " " << theo_dfdy << " " << abs(results[2] - theo_dfdy) << endl;
    cout << "d^2f/dxdy: " << results[3] << " " << theo_dfdxy << " " << abs(results[3] - theo_dfdxy) << endl;
    if(x < x_min || x > x_max || y < y_min || y > y_max)
        cout << "Point (x, y) = (" << x << ", " << y << ") is out of bound." << endl;
    cout << endl;
} // test()




















