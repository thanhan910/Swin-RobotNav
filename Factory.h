#pragma once

#include <string>
#include <vector>

#include "Grid.h"


using namespace std;
// Factory class
class Factory
{
public:
    static Grid* createGrid(string method, const vector<vector<int>>& configs, bool using_jump_ = false, bool using_gui_ = false);
};

