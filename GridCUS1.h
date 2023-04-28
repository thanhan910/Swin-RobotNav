#pragma once
#include "Grid.h"
/// <summary>
/// Dijkstra's algorithm
/// </summary>
class GridCUS1 : public Grid
{
public:
    GridCUS1(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) :
        Grid(configs, using_jump_, using_gui_) {};

    void perform_search() override;
};

