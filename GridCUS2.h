#pragma once
#include "GridInformed.h"
/// <summary>
/// Iterative Deepending A Star Search
/// </summary>
class GridCUS2 : public GridInformed
{
private:
    double bound;
    
    double search_recursion(const Location& current, const double& g);

    unordered_map<Location, Location> search_tree;

public:
    GridCUS2(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) : 
        GridInformed(configs, using_jump_, using_gui_), bound(-1) {};

    void perform_search() override;
};

