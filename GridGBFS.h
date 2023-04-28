#pragma once
#include "GridInformed.h"
/// <summary>
/// Greedy Best First Search
/// </summary>
class GridGBFS : public GridInformed
{
public:
    GridGBFS(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) : 
        GridInformed(configs, using_jump_, using_gui_) {};

    void perform_search();
};

