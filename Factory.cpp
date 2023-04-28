#include "Factory.h"

#include "GridDFS.h"
#include "GridBFS.h"
#include "GridGBFS.h"
#include "GridAS.h"
#include "GridCUS1.h"
#include "GridCUS2.h"

Grid* Factory::createGrid(string method, const vector<vector<int>>& configs, bool using_jump_, bool using_gui_)
{
    if (method == "DFS")
        return new GridDFS(configs, using_jump_, using_gui_);
    else if (method == "BFS")
        return new GridBFS(configs, using_jump_, using_gui_);
    else if (method == "GBFS")
        return new GridGBFS(configs, using_jump_, using_gui_);
    else if (method == "AS")
        return new GridAS(configs, using_jump_, using_gui_);
    else if (method == "CUS1")
        return new GridCUS1(configs, using_jump_, using_gui_);
    else if (method == "CUS2")
        return new GridCUS2(configs, using_jump_, using_gui_);
    else
        return nullptr;
}
