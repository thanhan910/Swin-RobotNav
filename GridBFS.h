#pragma once
#include "Grid.h"
/// <summary>
/// Breath-First search
/// </summary>
class GridBFS : public Grid
{
public:
    GridBFS(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) :
        Grid(configs, using_jump_, using_gui_) {};

    void perform_search() override;
};

