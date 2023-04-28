#include "GridCUS1.h"
#include <queue>

// State structure to store node in the frontier
struct StateCUS1
{
    Location location;
    double cost;
};

// comparator to use in priority queue
bool operator > (const StateCUS1& a, const StateCUS1& b)
{
    return a.cost > b.cost;
}

/// <summary>
/// Dijsktra's algorithm
/// </summary>
void GridCUS1::perform_search()
{
    unordered_map<Location, double> cost_so_far;

    priority_queue<StateCUS1, vector<StateCUS1>, greater<StateCUS1>> frontier;

    came_from[start] = start;
    number_of_nodes++;


    cost_so_far[start] = 0;

    frontier.push({ start, 0 });

    if(using_GUI)
    {
        GUI_increment_instructions_sequence();
        GUI_set_text(start, cost_so_far[start]);
    }

    while (!frontier.empty())
    {
        Location current = frontier.top().location; frontier.pop();

        if (using_GUI)
        {
            GUI_set_foreground(current, Color::Yellow);
        }

        if (is_goal(current))
        {
            set_goal_found(current);
            break;
        }

        if (using_GUI)
        {
            GUI_increment_instructions_sequence();
        }

        for (Location next : next_nodes(current))
        {
            double new_cost = cost_so_far[current] + cost(current, next);
            if (cost_so_far.find(next) == cost_so_far.end()
                || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                
                came_from[next] = current;
                number_of_nodes++;

                frontier.push({ next, new_cost });
                
                if (using_GUI)
                {
                    GUI_set_foreground(next, Color::Cyan);
                    GUI_set_text(next, new_cost);
                }
            }
        }

        if (using_GUI)
        {
            GUI_increment_instructions_sequence();
            GUI_set_foreground(current, Color::Blue);
        }
    }
}
