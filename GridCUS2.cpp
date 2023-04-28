#include "GridCUS2.h"

/// <summary>
/// Iterative Deepening A Star search
/// </summary>
void GridCUS2::perform_search()
{
    bound = heuristic(start);
    
    came_from[start] = start;

    search_tree[start] = start;

    
    if(using_GUI)
    {
        GUI_increment_instructions_sequence();
    }

    while (true)
    {
        double t = search_recursion(start, 0);

        number_of_nodes = came_from.size();

        if (is_goal_found()) return;

        if (t < 0)
        {
            return;
        }

        bound = t;
    }
}

double GridCUS2::search_recursion(const Location& current, const double& g)
{

    double f = g + heuristic(current);
    
    if(using_GUI)
    {
        GUI_set_foreground(current, Color::Yellow);
        GUI_set_text(current, f);
        GUI_increment_instructions_sequence();
    }

    if (f > bound)
    {
        if(using_GUI)
        {
            //GUI_increment_instructions_sequence();
            GUI_set_foreground(current, Color::White);
        }

        return f;
    }
       

    if (is_goal(current))
    {
        set_goal_found(current);
        return f;
    }

    double min_cost = -1;

    for (auto next : next_nodes(current))
    {
        if (!search_tree.count(next)) // if not visited yet
        {
            search_tree[next] = current;

            came_from[next] = current;
            
            if(using_GUI)
            {
                /*GUI_increment_instructions_sequence();
                GUI_set_foreground(next, Color::Cyan);*/

                GUI_increment_instructions_sequence();
                GUI_set_foreground(current, Color::Blue);
            }

            double t = search_recursion(next, g + 1);
            
            if(using_GUI)
            {
                GUI_set_foreground(current, Color::Yellow);
            }
            
            if (is_goal_found()) return t;
            
            if (min_cost == -1 || min_cost > t) min_cost = t;
            
            search_tree.erase(next);
        }
    }

    if(using_GUI)
    {
        //GUI_increment_instructions_sequence();
        GUI_set_foreground(current, Color::White);
        //GUI_set_text(current, ".");
    }

    return min_cost;
}
