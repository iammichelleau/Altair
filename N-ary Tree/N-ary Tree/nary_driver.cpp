#include "nary_driver.h"

OSINT LEAVES = 0;
OSINT LENGTH = 0;

int main(){
    OSINT *children = nullptr, *nodes_by_depth = nullptr, *queue = nullptr;
    double f, *point = nullptr, *distances = nullptr, *data = nullptr, **raw_data = nullptr;
    string input = "../../Input/nary_tree4d.txt";
    srand((unsigned OSINT)time(NULL));

    read_input(input, &raw_data, &children, &nodes_by_depth);
    
    LENGTH = handle_input(raw_data, children, nodes_by_depth, DIM, LEAVES);
    
    initialization(&point, &data, &distances, &queue);
    
    f = nary_interp(point, raw_data, data, distances, queue, children, nodes_by_depth, DIM, LEAVES);
    
    test(f, point, data, children, nodes_by_depth);
    free(children, nodes_by_depth, queue, point, distances, data, raw_data);

    return 0;
} //  main()

void read_input(string input, double ***raw_data, OSINT **children, OSINT **nodes_by_depth){
    get_dimensions(input);
    raw_initialization(raw_data, children, nodes_by_depth);
    get_values(input, raw_data);
} // read_input()

void raw_initialization(double ***raw_data, OSINT **children, OSINT **nodes_by_depth){
    OSINT i, j;
    
    *raw_data = new double*[LEAVES];
    for(i = 0; i < LEAVES; ++i)
        (*raw_data)[i] = new double[DIM + 1];
    
    for(i = 0; i < LEAVES; i++){
        for(j = 0; j < (DIM + 1); j++)
            (*raw_data)[i][j] = 0;
    } // for i
    
    *children = new OSINT[DIM * LEAVES + 1];
    for(i = 0; i < (DIM * LEAVES + 1); i++)
        (*children)[i] = 0;
    
    *nodes_by_depth = new OSINT[DIM + 2];
    for(i = 0; i < (DIM + 2); i++)
        (*nodes_by_depth)[i] = 0;
} // raw_initialization()

void initialization(double **point, double **data, double **distances, OSINT **queue){
    OSINT i, len;
    double min, max;
    
    min = 100.0; max = 300.0;
    
    *point = new double[DIM];
    for(i = 0; i < DIM; i++)
        (*point)[i] = (max - min) * ((double)rand() / (double)RAND_MAX) + min;
    
    (*data) = new double[LENGTH];
    for(i = 0; i < LENGTH; i++)
        (*data)[i] = 0;
    
    len = 0;
    for(i = 0; i < DIM; i++)
        len += pow(2, i);
    (*distances) = new double[len];
    for(i = 0; i < len; i++)
        (*distances)[i] = 0;
    
    len = pow(2, DIM - 1);
    (*queue) = new OSINT[len];
    for(i = 0; i < len; i++)
        (*queue)[i] = 0;
} // initialization()

void free(OSINT *children, OSINT *nodes_by_depth, OSINT *queue,
          double *point, double *distances, double *data, double **raw_data){
    OSINT i;
    
    delete []children;
    delete []nodes_by_depth;
    delete []queue;
    delete []point;
    delete []distances;
    delete []data;
    
    for(i = 0; i < LEAVES; i++)
        delete []raw_data[i];
    delete []raw_data;
} // free()

void get_dimensions(string input){
    string y, line;
    vector<string> items;
    vector<string>::iterator it;
    
    ifstream file(input);
    
    if (file.is_open()){
        getline(file,line);
        LEAVES++;
        
        while(getline(file,line))
            LEAVES++;
        
        file.close();
    } // if()
    
    else
        cout << "Unable to open file."; 
} // get_dimensions()

void get_values(string input, double ***raw_data){
    OSINT i = 0, j = 0;
    string line;
    vector<string> items;
    vector<string>::iterator it;
    
    ifstream file(input);
    
    if (file.is_open()){
        getline(file,line);
        items = split(line, ' ');
        
        for(j = 0; j < (DIM + 1); j++)
            (*raw_data)[i][j] = stod(items[j]);
        i++;
        
        while(getline(file,line)){
            items = split(line, ' ');
            
            for(j = 0; j < (DIM + 1); j++)
                (*raw_data)[i][j] = stod(items[j]);
            i++;
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

void test(double f, double *point, double *data, OSINT *children, OSINT *nodes_by_depth){
    OSINT i, NODES = 1;
    
    cout << "DIM: " << DIM << endl;
    cout << "LEAVES: " << LEAVES << endl;
    
    i = 0;
    while(children[i] != 0){
        NODES += children[i];
        i++;
    } // while
    cout << "NODES: " << NODES << endl;
    
//    cout << "Nodes by depth: ";  
//    for(i = 0; i < (DIM + 2); i++)
//        cout << nodes_by_depth[i] << " ";
//    cout << endl;
    
    cout << "LENGTH: " << LENGTH << endl;
    
//    cout << "n: ";
//    for(i = 0; i < (DIM * LEAVES + 1); i++)
//        cout << children[i] << " ";
//    
//    cout << endl << "data: ";
//    for(i = 0; i < LENGTH; i++)
//        cout << data[i] << " ";
//    cout << endl << endl;
    
    cout << "Interpolating (" << point[0];
    for(i = 1; i < DIM; i++)
        cout << ", " << point[i];
    cout << ")... " << f << endl;
} // test()
