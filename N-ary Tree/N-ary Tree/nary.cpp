#include "nary.h"

double nary_interp(double *point, double **raw_data, double *data, double *distances, OSINT *queue, OSINT *children, OSINT *nodes_by_depth,
                 OSINT DIM, OSINT LEAVES){
    OSINT NODES, LENGTH;
    double f;
    
    NODES = get_NODES(children);
    LENGTH = get_LENGTH(LEAVES, NODES);
    
    make_tree(raw_data, data, children, nodes_by_depth, DIM, LEAVES, NODES, LENGTH);
    f = interp_tree(point, data, distances, queue, children, DIM, LEAVES, NODES, LENGTH);
    
    return f; 
} // nary_interp()

void make_tree(double **raw_data, double *data, OSINT *children, OSINT *nodes_by_depth,
          OSINT DIM, OSINT LEAVES, OSINT NODES, OSINT LENGTH){
    OSINT i, j, k;
    double value, parent;
    
    // Values
    k = 0;
    data[k++] = INF;
    
    for(j = DIM; j > 0; j--){
        value = raw_data[0][j];
        data[k++] = value;
        
        for(i = 0; i < LEAVES; i++){
            if(value != raw_data[i][j]){
                value = raw_data[i][j];
                data[k++] = value;
            } //  if
        } // for i
    } // for j
    
    j = 0;
    for(i = 0; i < LEAVES; i++){
        value = raw_data[i][j];
        data[k++] = value;
    } // for i
    
    // Number of Children
    i = 0;
    while(children[i] != 0){
        data[k++] = children[i];
        i++;
    } // while
    
    for(i = 0; i < LEAVES; i++)
        data[k++] = 0;
    
    // Parent Locations
    data[k++] = INF;
    for(i = 0; i < children[0]; i++)
        data[k++] = 0;
    
    for(j = (DIM - 1); j > -1; j--){
        value = raw_data[0][j];
        parent = raw_data[0][j + 1];
        data[k++] = get_index(data, nodes_by_depth, parent, j, DIM, NODES);
        
        for(i = 1; i < LEAVES; i++){
            if(value != raw_data[i][j]){
                value = raw_data[i][j];
                
                if(parent != raw_data[i][j + 1])
                    parent = raw_data[i][j + 1];
                data[k++] = get_index(data, nodes_by_depth, parent, j, DIM, NODES);
            } // if
        } // for i
    } // for j
    
    // Children Locations
    k = 1;
    for(i = 0; i < NODES; i++){
        for(j = 0; j < get_num(data, i, NODES); j++)
            data[3 * NODES + i * LEAVES + j] = k++;
    } // for i
    
    //    OSINT i, j, k, l, c, loc, curr_child;
    //    double curr;
    //
    //    i = 0;
    //    loc = 0;
    //
    //    data[i++] = INF;
    //    data[i++] = children_root;
    //    i++;
    //    loc = 3 + children_root;
    //
    //    for(j = 0; j < children_root; j++){
    //        data[i++] = loc;
    //        loc += 3 + children[0][j];
    //    } // for j
    //
    //    l = 0;
    //    c = 0;
    //
    //    for(k = DIM; k > 1; k--){
    //        curr = raw_data[0][k];
    //        curr_child = children[l][c++];
    //        data[i++] = curr;
    //        data[i++] = curr_child;
    //        i++;
    //
    //        i += curr_child;
    //
    //        for(j = 0; j < LEAVES; j++){
    //            if(curr != raw_data[j][k]){
    //                curr = raw_data[j][k];
    //                data[i++] = curr;
    //                data[i++] = curr_child;
    //                i++;
    //
    //                i += curr_child;
    //            } //  if
    //        } // for j
    //
    //        l++;
    //        c = 0;
    //    } // for k
    //
    //    l--;
    //    c = 0;
    //    k = 1;
    //    curr = raw_data[0][k];
    //    data[i++] = curr;
    //    data[i++] = children[l][c++];
    //    i += children[l][c - 1];
    //
    //    for(j = 0; j < LEAVES; j++){
    //        if(curr != raw_data[j][k]){
    //            curr = raw_data[j][k];
    //            data[i++] = curr;
    //            data[i++] = children[l][c++];
    //
    //            i += children[l][c - 1];
    //        } //  if
    //    } // for j
    //    
    //    k = 0;
    //    for(j = 0; j < LEAVES; j++){
    //        curr = raw_data[j][k];
    //        data[i++] = curr;
    //    } // for j
} // make_tree()

double interp_tree(double *point, double *data, double *distances, OSINT *queue, OSINT *children,
                 OSINT DIM, OSINT LEAVES, OSINT NODES, OSINT LENGTH){
    OSINT i, j, ind, dim, start, end, parent, num, L_queue, L_dist;
    double d, f, f1, f2;
    
    i = 0;
    dim = 0;
    parent = 0;
    num = get_num(data, parent, NODES);
    start = get_child_index(data, parent, 0, NODES, LEAVES);
    end = get_child_index(data, parent, num - 1, NODES, LEAVES) + 1;
    
    L_queue = pow(2, DIM - 1);
    L_dist = 0;
    for(j = 0; j < DIM; j++)
        L_dist += pow(2, j);
    
    ind = locate(point[dim], data, start, end, NODES);
    push(queue, ind, L_queue);
    push(queue, ind + 1, L_queue);
    distances[i++] = distance(point[dim], data, ind);
    
    for(dim = 1; dim < DIM - 1; dim++){
        for(j = 0; j < pow(2, dim); j++){
            parent = pop(queue, L_queue);
            num = get_num(data, parent, NODES);
            start = get_child_index(data, parent, 0, NODES, LEAVES);
            end = get_child_index(data, parent, num - 1, NODES, LEAVES) + 1;
            
            ind = locate(point[dim], data, start, end, NODES);
            push(queue, ind, L_queue);
            push(queue, ind + 1, L_queue);
            distances[i++] = distance(point[dim], data, ind);
        } // for j
    } // for dim
    
    double *interps = new double[L_queue];
    for(j = 0; j < L_queue; j++)
        interps[i] = 0.0;
    
    for(j = 0; j < L_queue; j++){
        parent = queue[j];
        num = get_num(data, parent, NODES);
        start = get_child_index(data, parent, 0, NODES, LEAVES);
        end = get_child_index(data, parent, num - 1, NODES, LEAVES) + 1;
        ind = locate(point[dim], data, start, end, NODES);
        d = distance(point[dim], data, ind);
        f = (1 - d) * data[ind] + d * data[ind + 1];
        
        distances[i++] = d;
        push(interps, f, L_queue);
    } // for j
    
//    cout << "Distancces: ";
//    for(i = 0; i < L_dist; i++)
//        cout << distances[i] << " ";
//    cout << endl;
//    
//    cout << "Interps: ";
//    for(i = 0; i < L_queue; i++)
//        cout << interps[i] << " ";
//    cout << endl;
    
    i = L_dist - pow(2, DIM - 1) - pow(2, DIM - 2);
    for(dim = DIM - 2; dim > 0; dim--){
        for(j = 0; j < pow(2, dim); j++){
            f1 = pop(interps, L_queue);
            f2 = pop(interps, L_queue);
            
//            cout << i << endl;
            d = distances[i++];
            
            f = (1 - d) * f1 + d * f2;
            push(interps, f, L_queue);
//            print(interps, L_queue);
        } // for j
        i = i - pow(2, dim) - pow(2, dim - 1);
    } // while
    
    f = (1.0 - distances[0]) * interps[0] + distances[0] * interps[1];
    return f;
} // interp_tree()

OSINT locate(double point, double *data, OSINT start, OSINT end, OSINT NODES){
    OSINT i;
    
    for(i = start; i < end; i++){
        if(data[i] > point){
            i = i - 1;
            break;
        } // if
    } // for i
    
    if(i == (start - 1))
    i += 1;
    if(i == end)
        i -= 2;

    return i;
} // locate()

double distance(double point, double *data, OSINT ind){
    double distance;
    
    distance = (point - data[ind]) / (data[ind + 1] - data[ind]);
    if(distance < 0)
        distance = 0;
    if(distance > 1)
        distance = 1;
    
    return distance;
} // distance()

OSINT get_index(double *data, OSINT *nodes_by_depth, double value, OSINT depth, OSINT DIM, OSINT NODES){
    OSINT i, j, sum, d_invert, d;
    
    depth += 1;
    
    if(value == INF)
        return 0;
    
    for(i = 1; i < NODES; i++){
        sum = 0;
        for(j = 0; j < (DIM + 2); j++){
            sum += nodes_by_depth[j];
            if(sum > i){
                d_invert = j;
                break;
            } // if
        } // for j
        
        d = DIM + 1;
        for(j = 0; j < d_invert; j++)
            d--;
            
        if(data[i] == value && d == depth)
            return i;
    } // for i
    
    return -1;
} // get_index()

double get_value(double *data, OSINT index){
    return data[index];
} // get_value()

OSINT get_num(double *data, OSINT index, OSINT NODES){
    return data[NODES + index];
} // get_num()

OSINT get_parent_index(double *data, OSINT index, OSINT NODES){
    return data[2 * NODES + index];
} // get_parent_index()

OSINT get_child_index(double *data, OSINT index, OSINT child, OSINT NODES, OSINT LEAVES){
    return data[3 * NODES + index * LEAVES + child];
} // get_child_index()

OSINT handle_input(double **raw_data, OSINT *children, OSINT *nodes_by_depth, OSINT DIM, OSINT LEAVES){
    OSINT NODES, LENGTH;
    
    get_children(raw_data, children, nodes_by_depth, DIM, LEAVES);
    NODES = get_NODES(children);
    LENGTH = get_LENGTH(LEAVES, NODES);
    
    return LENGTH;
} // handle_input()

void get_children(double **raw_data, OSINT *children, OSINT *nodes_by_depth, OSINT DIM, OSINT LEAVES){
    OSINT i, j, k, d, sum = 0;
    double curr, curr_parent;
    
    k = 0;
    d = 0;
    
    j = DIM;
    children[k] = 1;
    curr = raw_data[0][j];
    for(i = 1; i < LEAVES; i++){
        if(curr != raw_data[i][j]){
            curr = raw_data[i][j];
            children[k]++;
        } // if
    } // for i
    k++;
    
    nodes_by_depth[d++] = 1;
    nodes_by_depth[d++] = children[0];
    
    for(j = (DIM - 1); j > 0; j--){
        children[k] = 1;
        sum = 1;
        curr = raw_data[0][j];
        curr_parent = raw_data[0][j + 1];
        
        for(i = 1; i < LEAVES; i++){
            if(curr_parent == raw_data[i][j + 1]){
                if(curr != raw_data[i][j]){
                    curr = raw_data[i][j];
                    children[k]++;
                    sum++;
                } // if
            } // if
            
            if(curr_parent != raw_data[i][j + 1]){
                curr = raw_data[i][j];
                curr_parent = raw_data[i][j + 1];
                k++;
                children[k] = 1;
                sum++;
            } // if
        } // for i
        k++;
        nodes_by_depth[d++] = sum;
    } // for j
    nodes_by_depth[d++] = sum;
    
    for(i = 0; i < LEAVES; i++)
        children[k++] = 1;
} // get_children()

OSINT get_NODES(OSINT *children){
    OSINT i, NODES;
    
    i = 0;
    NODES = 1;
    
    while(children[i] != 0){
        NODES += children[i];
        i++;
    } // while
    
    return NODES;
} // get_NODES()

OSINT get_LENGTH(OSINT LEAVES, OSINT NODES){
    OSINT LENGTH;

    LENGTH = 3 * NODES + (NODES - LEAVES) * LEAVES;
    
    return LENGTH;
} // get_LENGTH()

void push(OSINT *queue, OSINT ind, OSINT L){
    OSINT i;
    
    if(queue[L - 1] != 0)
        cout << "ERROR: queue overflow!" << endl;
    
    for(i = 0; i < L; i++){
        if(queue[i] == 0){
            queue[i] = ind;
            break;
        } // if
    } // for i
} // push()

void push(double *queue, double data, OSINT L){
    OSINT i;
    
    if(queue[L - 1] != 0 && (queue[L - 1] > MIN_TOL))
        cout << "ERROR: queue overflow!" << endl;
    
    for(i = 0; i < L; i++){
        if(queue[i] == 0 || queue[i] < MIN_TOL){
            queue[i] = data;
            break;
        } // if
    } // for i
} // push()

OSINT pop(OSINT *queue, OSINT L){
    OSINT i, ind;
    
    ind = queue[0];
    
    for(i = 0; i < (L - 1); i++){
        queue[i] = queue[i + 1];
        queue[i + 1] = 0;
    } // for i
    
    return ind;
} // pop()

double pop(double *queue, OSINT L){
    OSINT i;
    double data;
    
    data = queue[0];
    
    for(i = 0; i < (L - 1); i++){
        queue[i] = queue[i + 1];
        queue[i + 1] = 0;
    } // for i
    
    return data;
} // pop()

OSINT length(double *queue, OSINT L){
    OSINT i;
    
    for(i = 0; i < L; i++)
        if(queue[i] == 0)
            return i;
    
    return i;
} // length()

void print(OSINT *array, OSINT L){
    OSINT i;
    
    for(i = 0; i < L; i++)
        cout << array[i] << " ";
    cout << endl;
} // print()

void print(double *array, OSINT L){
    OSINT i;
    
    for(i = 0; i < L; i++)
        cout << array[i] << " ";
    cout << endl;
} // print()
