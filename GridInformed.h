#pragma once
#include "Grid.h"
/// <summary>
/// Abstract class for Informed search algorithms
/// The heuristic function is implemented here
/// </summary>
class GridInformed : public Grid
{
protected:
    virtual double heuristic(const Location& current, const Location& goal);
    double heuristic(const Location& current);

public:
    GridInformed(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) 
        : Grid(configs, using_jump_, using_gui_) {};
};

