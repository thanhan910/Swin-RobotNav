#include "GridDFS.h"

void GridDFS::perform_search()
{
    came_from[start] = start;
    number_of_nodes++;

    if(using_GUI)
    {
        GUI_increment_instructions_sequence();
    }

    dfs_recursion(start);
}

bool GridDFS::dfs_recursion(Location& current)
{
    if(using_GUI)
    {
        GUI_set_foreground(current, Color::Yellow);
        GUI_set_text(current, "0");
    }

    if (is_goal(current))
    {
        set_goal_found(current);
        return true;
    }

    for (Location next : next_nodes(current))
    {
        if (!came_from.count(next)) // not visited
        {
            came_from[next] = current;
            number_of_nodes++;

            if(using_GUI)
            {
                GUI_increment_instructions_sequence();
                GUI_set_foreground(current, Color::Blue);
            }

            bool result = dfs_recursion(next);
            
            if(using_GUI)
            {
                GUI_set_foreground(current, Color::Yellow);
            }

            if (result) return true;
        }
    }

    if(using_GUI)
    {
        GUI_increment_instructions_sequence();
        GUI_set_foreground(current, Color::Blue);
    }

    return false;
}


