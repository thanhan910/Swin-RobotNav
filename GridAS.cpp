#include "GridAS.h"
#include <queue>

// State structure to store node in the frontier
struct StateAS
{
    Location location;
    double priority;
    double heuristic;
};

// comparator to use in priority queue
bool operator > (const StateAS& a, const StateAS& b)
{
    return make_pair(a.priority, a.heuristic) > make_pair(b.priority, b.heuristic);
}


/// <summary>
/// A Star search
/// </summary>
void GridAS::perform_search()
{
    priority_queue<StateAS, vector<StateAS>, greater<StateAS>> frontier;
    unordered_map<Location, double> cost_so_far;

    came_from[start] = start;
    number_of_nodes++;

    double new_cost = 0;
    cost_so_far[start] = new_cost;
    
    double heuristic_cost = heuristic(start);
    double priority = new_cost + heuristic_cost;    
    
    frontier.push({ start, priority, heuristic_cost });

    if (using_GUI)
    {
        GUI_increment_instructions_sequence();
        GUI_set_text(start, to_string((int)priority) + "," + to_string((int)heuristic_cost));
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
            return;
        }

        if (using_GUI)
        {
            GUI_increment_instructions_sequence();
        }

        for (Location next : next_nodes(current))
        {
            double new_cost = cost_so_far[current] + cost(current, next);
            if (!cost_so_far.count(next) || // cost not calculated
                new_cost < cost_so_far[next]) // new cost is lower than cost so far
            {
                cost_so_far[next] = new_cost;
                double heuristic_cost = heuristic(next);
                double priority = new_cost + heuristic_cost;
                frontier.push({ next, priority, heuristic_cost });
                
                came_from[next] = current;
                number_of_nodes++;
                
                if (using_GUI)
                {
                    GUI_set_foreground(next, Color::Cyan);
                    GUI_set_text(next, to_string((int)priority) + "," + to_string((int)heuristic_cost));
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
