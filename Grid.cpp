#include "Grid.h"
#include <algorithm>
#include <cmath>
#include <iostream>


Grid::Grid(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) :
    width(configs[0][1]), 
    height(configs[0][0]), 
    start{ configs[1][0],configs[1][1] }, 
    goal_final{ -1, -1 },
    using_jump(using_jump_),
    using_GUI(using_gui_),
    GUI_Grid(nullptr)
{
    for (size_t i = 0; i < configs[2].size(); i += 2)
    {
        add_goal(configs[2][i], configs[2][i + 1]);
    }

    for (int i = 3; i < configs.size(); i++)
    {
        add_wall(configs[i][0], configs[i][1], configs[i][2], configs[i][3]);
    }

    if (using_jump)
    {
        using_saving_next_cells = true;
    }

    if (using_GUI)
    {
        GUI_init_grid();
    }
}

Grid::~Grid()
{

}


bool Grid::is_in_bounds(const Location& id) const
{
    return 0 <= id.x && id.x < width
        && 0 <= id.y && id.y < height;
}

void Grid::add_wall(int x, int y, int w, int h)
{
    walls.push_back({ {x, y}, {x + w - 1, y + h - 1} });
}

bool Grid::is_wall(const Location& id) const
{
    for (auto wall : walls)
    {
        if (wall.first.x <= id.x && id.x <= wall.second.x &&
            wall.first.y <= id.y && id.y <= wall.second.y)
        {
            return true;
        }
    }

    return false;
}



// Array of directions to traverse the next node
// This order ensures that the sequence of adding the child nodes 
// will be up-left-down-right
const Location Grid::D_NEIGHBORS[4] = {
    Location{0, -1}, // Up
    Location{-1, 0}, // Left
    Location{0, 1}, // Down
    Location{1, 0}, // Right
};

// Return the next nodes of the node
vector<Location> Grid::next_nodes(const Location& id)
{
    if (using_saving_next_cells && next_nodes_map.count(id))
    {
        return next_nodes_map[id];
    }

    vector<Location> arr;

    for (Location dir : D_NEIGHBORS)
    {
        Location next{ id.x + dir.x, id.y + dir.y };
        bool next_is_wall = is_wall(next);
        bool next_is_in_bounds = is_in_bounds(next);
        if (!next_is_wall && next_is_in_bounds)
        {
            arr.push_back(next);
        }
        else if (using_jump && next_is_wall)
        {
            bool prev_is_wall = next_is_wall;

            while (next_is_in_bounds)
            {
                next = { next.x + dir.x, next.y + dir.y };
                
                next_is_in_bounds = is_in_bounds(next);
                
                if (!next_is_in_bounds) break;

                next_is_wall = is_wall(next);

                if (prev_is_wall && !next_is_wall && next_is_in_bounds)
                {
                    arr.push_back(next);
                }

                prev_is_wall = next_is_wall;
            }
        }
    }

    if (using_saving_next_cells)
    {
        next_nodes_map[id] = arr;
    }

    return arr;
}

// Return the cost to travel from current node to next node
size_t Grid::cost(const Location& current, const Location& next) const
{
    if (!using_jump)
    {
        return 1;
    }
    else
    {
        int steps = abs(next.x - current.x) + abs(next.y - current.y);
        return pow(2, steps - 1);
    }
}



void Grid::add_goal(int x, int y)
{
    goals.push_back({ x, y });
}


bool Grid::is_goal(const Location& id) const
{
    for (auto goal : goals)
    {
        if (id == goal) return true;
    }

    return false;
}


bool Grid::is_goal_found() const
{
    return goal_final.is_not_null();
}


void Grid::set_goal_found(const Location& goal_found_)
{
	goal_final = goal_found_;
}

void Grid::construct_path()
{
    path.clear();

    if (!is_goal_found()) return; // no path can be found

    Location current = goal_final;

    while (current != start)
    {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
}

int Grid::get_number_of_nodes()
{
    return number_of_nodes;
}

void Grid::print_path()
{
    construct_path();
    
    // Print path
    
    if (!is_goal_found())
    {
        cout << "No solution found";
    }
    
    else
    {
        Location prev = path[0];

        for (int i = 1; i < path.size(); i++)
        {
            Location curr = path[i];
            int dx = curr.x - prev.x;
            int dy = curr.y - prev.y;
            if (dx == -1) cout << "left; ";
            else if (dx == 1) cout << "right; ";
            else if (dy == -1)  cout << "up; ";
            else if (dy == 1) cout << "down; ";
            else if (using_jump)
            {
                if (dx < 0) cout << "jump_left("<< -dx << "); ";
                else if (dx > 0) cout << "jump_right(" << dx << "); ";
                else if (dy < 0)  cout << "jump_up(" << -dy << "); ";
                else if (dy > 0) cout << "jump_down(" << dy << "); ";
            }
            prev = curr;
        }
    }

    cout << endl;
}
