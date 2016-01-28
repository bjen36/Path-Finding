#ifndef OUTPUT_H
#define OUTPUT_H
#include <vector>
#include <iostream>

#include "Common.h"
using namespace std;

// updates 3D vector with correct path
void update_M(vector<vector<vector<path_tracker> > > &, deque<coordinates> &);

// prints 3D vector of M
void print_M(vector<vector<vector<path_tracker> > > &, int, int);

// prints traceback of L
void print_L(deque<coordinates> &, int, int);

#endif