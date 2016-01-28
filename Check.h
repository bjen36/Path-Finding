#ifndef CHECK_H
#define CHECK_H
#include <vector>
#include <iostream>
#include "Common.h"
using namespace std;


bool north_check(vector<vector<vector<path_tracker> > > &, const coordinates &, bool &);
// EFFECTS: returns true if the north route is possible to move to

bool east_check(vector<vector<vector<path_tracker> > > &, int, const coordinates &, bool &);
// EFFECTS: returns true if the east route is possible to move to

bool south_check(vector<vector<vector<path_tracker> > > &, int, const coordinates &, bool &);
// EFFECTS: returns true if the south route is possible to move to

bool west_check(vector<vector<vector<path_tracker> > > &, const coordinates &, bool &);
// EFFECTS: returns true if the west route is possible to move to

bool portal_check(vector<vector<vector<path_tracker> > > &, int, const coordinates &, bool &, int *);
// EFFECTS: checks if the move to destination is a portal and 
// and checks is in range of the room number.

#endif