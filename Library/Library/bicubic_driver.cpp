#include "bicubic_driver.h"

OSINT X = 1;
OSINT MAX_X = 1;
OSINT Y = 1;

OSINT main(){
    OSINT i, in, n;
    double x, y, min, max;
    string input;
    srand((unsigned OSINT)time(NULL));
    
    for(in = 0; in < 4; in++){
        OSINT *istack = ivector(1, NSTACK), *index = nullptr, *interp_index = new OSINT [3],
            *x_ind = new OSINT[2], *y_ind = new OSINT[2], *bcucof_wt = new OSINT[16*16];
        double *x_array = nullptr, ***raw_data = nullptr, ***data = nullptr,
            *d_array = nullptr, *f_array = nullptr,
            *f = new double[4], *f1 = new double[4], *f2 = new double[4], *f12 = new double[4],
            *results = new double[4], *interp_results = new double[10], *theo_results = new double[4], **C = new double*[4],
            *bcucof_x = new double[16], *bcucof_cl = new double [16];
        
        for(i = 0; i < 4; ++i)
            C[i] = new double[4];
        
        if(in == 0){
            input = "../Input/plane.txt";
            cout << "Interpolating with a plane... " << endl;
        } // if
        if(in == 1){
            input = "../Input/const_plane.txt";
            cout << "Interpolating with a constant plane... " << endl;
        } // if
        if(in == 2){
            input = "../Input/sin_add.txt";
            cout << "Interpolating with sin(x + y)... " << endl;
        } // if
        if(in == 3){
            input = "../Input/sin_times.txt";
            cout << "Interpolating with sin(x * y)... " << endl;
        } // if

		read_input(input, &index, &x_array, &raw_data); 
        
        X = handle_input(x_array, index, istack, X);
        
		initialization(&d_array, &f_array, &data, &bcucof_wt);

		uniform_grid(x_array, d_array, f_array, interp_index, interp_results, &data, raw_data, 
			X, MAX_X, Y); 
        
        for(n = 0; n < N; n++){
            min = -10.0; max = 10.0;
            x = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
            min = -1.0; max = 1.0;
            y = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
            
            bicubic_interp(x, y, x_ind, y_ind, bcucof_wt, bcucof_x, bcucof_cl, f, f1, f2, f12, &C, data, X, Y, results);
            test(in, x, y, results, theo_results);
        } // for n
        
        free(istack, index, interp_index, x_ind, y_ind, x_array, d_array, f_array, f, f1, f2, f12,
             results, interp_results, theo_results, bcucof_x, bcucof_cl, C, raw_data, data);
    } // for in
    
    return 0;
} // main()

void read_input(string input, OSINT **index, double **x_array, double ****data){
    get_dimensions(input);
    raw_initialization(index, x_array, data);
    get_values(input, x_array, data);
} // read_input()

void raw_initialization(OSINT **index, double **x_array, double ****data){
    OSINT i, j, k;
    
    *index = new OSINT[X];
    for(i = 0; i < X; i++)
        (*index)[i] = i;
    
    *x_array = new double[X];
    
    *data = new double**[Y];
    for(i = 0; i < Y; i++){
        (*data)[i] = new double*[MAX_X];
        for(j = 0; j < MAX_X; j++)
            (*data)[i][j] = new double[3];
    } // for i
    
    for(i = 0; i < Y; i++){
        for(j = 0; j < MAX_X; j++){
            for(k = 0; k < 3; k++)
                (*data)[i][j][k] = -INF;
        } // for j
    } // for i
} // raw_initialization()

void initialization(double **d_array, double **f_array, double ****data, OSINT **bcucof_wt){
	OSINT i, j; 

	(*data) = new double**[Y];
    for(i = 0; i < Y; i++){
        (*data)[i] = new double*[X];
        for(j = 0; j < X; j++)
            (*data)[i][j] = new double[3];
    } // for i
        
    (*d_array) = new double[X];
    (*f_array) = new double[X];
    
    OSINT wt[16*16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        -3, 0, 0, 3, 0, 0, 0, 0, -2, 0, 0, -1, 0, 0, 0, 0,
        2, 0, 0, -2, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, -3, 0, 0, 3, 0, 0, 0, 0, -2, 0, 0, -1,
        0, 0, 0, 0, 2, 0, 0, -2, 0, 0, 0, 0, 1, 0, 0, 1,
        -3, 3, 0, 0, -2, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, -3, 3, 0, 0, -2, -1, 0, 0,
        9, -9, 9, -9, 6, 3, -3, -6, 6, -6, -3, 3, 4, 2, 1, 2,
        -6, 6, -6, 6, -4,-2, 2, 4, -3, 3, 3, -3, -2, -1, -1, -2,
        2, -2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 2, -2, 0, 0, 1, 1, 0, 0,
        -6, 6, -6, 6, -3, -3, 3, 3, -4, 4, 2, -2, -2, -2, -1, -1,
        4, -4, 4, -4, 2, 2, -2, -2, 2, -2, -2, 2, 1, 1, 1, 1};
    
    for(i = 0; i < (16 * 16); i++)
        (*bcucof_wt)[i] = wt[i];
} // initialization()

void get_dimensions(string input){
    OSINT n = 1;
    string y, line;
    vector<string> items;
    vector<string>::iterator it;
    
    ifstream file(input);
    
    if (file.is_open()){
        getline(file,line);
        items = split(line, ' ');
        y = *(items.end() - 1);
        
        while(getline(file,line)){
            items = split(line, ' ');
            n++;
            
            if(y != *(items.end() - 1)){
                y = *(items.end() - 1);
                Y++;
                n = 1;
            } // if
            if(n > MAX_X)
                MAX_X = n;
            X++;
        } // while()
        file.close();
    } // if()
    
    else
        cout << "Unable to open file.";
} // get_dimensions

void get_values(string input, double **x_array, double ****data){
    OSINT i = 0, j = 0, k = 0, num_x = 0;
    string x, y, line;
    vector<string> items;
    vector<string>::iterator it;
    
    ifstream file(input);
    
    if (file.is_open()){
        getline(file,line);
        items = split(line, ' ');
        x = *(items.end() - 2);
        y = *(items.end() - 1);
        (*x_array)[num_x] = stod(x);
        
        for(k = 0; k < 3; k++)
            (*data)[i][j][k] = stod(items[k]);
        j++;
        
        while(getline(file,line)){
            items = split(line, ' ');
            x = *(items.end() - 2);
            
            if(y != *(items.end() - 1)){
                y = *(items.end() - 1);
                i++;
                j = 0;
            } // if
            
            num_x++;
            (*x_array)[num_x] = stod(x);
            
            for(k = 0; k < 3; k++)
                (*data)[i][j][k] = stod(items[k]);
            j++;
        } // while()
        file.close();
    } // if()
    
    else
        cout << "Unable to open file.";
} // get_values()

void test(OSINT in, double x, double y, double *results, double *theo_results){
    OSINT i; 
	
	if(in == 0){
        // Plane
        theo_results[0] = x+y;
        theo_results[1] = 1;
        theo_results[2] = 1;
        theo_results[3] = 0;
    } // if
    
    if(in == 1){
        // Constant Plane
        theo_results[0] = 10;
        theo_results[1] = 0;
        theo_results[2] = 0;
        theo_results[3] = 0;
    } // if
    
    if(in == 2){
        // Sine (Add)
        theo_results[0] = sin(x+y);
        theo_results[1] = cos(x+y);
        theo_results[2] = cos(x+y);
        theo_results[3] = -sin(x+y);
    } // if
    
    if(in == 3){
        // Sine (Times)
        theo_results[0] = sin(x*y);
        theo_results[1] = cos(x*y)*y;
        theo_results[2] = cos(x*y)*x;
        theo_results[3] = cos(x*y) - x * y * sin(x*y);
    } // if

	cout << "(x, y) = (" << x << ", " << y << ")" << endl;
    cout << "Errors: ";
    for(i = 0; i < 4; i++)
        cout << abs(results[i] - theo_results[i]) << " ";
    cout << endl << endl;
} // test()

template<typename Out>
void split(const string &s, char delim, Out result){
    string item;
    stringstream ss;
    ss.str(s);
    while(getline(ss, item, delim)){
        *(result++) = item;
    } // while()
} // split()

vector<string> split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
} // split()

OSINT *ivector(long nl, long nh){
    OSINT *v;
    
    v=(OSINT *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(OSINT)));
    if (!v) cout << "ERROR: allocation failure in ivector()." << endl;
    return v-nl+NR_END;
} // ivector()

void free(OSINT *istack, OSINT *index, OSINT *interp_index, OSINT *x_ind, OSINT *y_ind,
          double *x_array, double *d_array, double *f_array, double *f, double *f1, double *f2, double *f12,
          double *results, double *interp_results, double *theo_results,
          double *bcucof_x, double *bcucof_cl,
          double **C, double ***raw_data, double ***data){
    
    OSINT i, j;
    
    delete []istack;
    delete []index;
    delete []interp_index;
    delete []x_ind;
    delete []y_ind;
    delete []x_array;
    delete []d_array;
    delete []f_array;
    delete []f;
    delete []f1;
    delete []f2;
    delete []f12;
    delete []results;
    delete []interp_results;
    delete []theo_results;
    
    for(i = 0; i < 4; i++)
        delete [](C[i]);
    delete []C;
    
    for(i = 0; i < Y; i++){
        for(j = 0; j < MAX_X; j++)
            delete [](raw_data[i][j]);
        delete [](raw_data[i]);
    } // for i
    delete []raw_data;
    
    for(i = 0; i < Y; i++){
        for(j = 0; j < X; j++)
            delete [](data[i][j]);
        delete [](data[i]);
    } // for i
    delete []data;
} // free()
