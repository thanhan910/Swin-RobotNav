#pragma once
#include "Grid.h"
/// <summary>
/// Depth-First Search
/// </summary>
class GridDFS : public Grid
{
private:
    bool dfs_recursion(Location& current);
public:
    GridDFS(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) :
        Grid(configs, using_jump_, using_gui_) {};

    void perform_search() override;
};

