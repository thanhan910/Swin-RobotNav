#include "GridGBFS.h"
#include <queue>

// State structure to store node in the frontier
struct StateGBFS
{
    Location location;
    double heuristic;
};

// comparator to use in priority queue
bool operator > (const StateGBFS& a, const StateGBFS& b)
{
    return a.heuristic > b.heuristic;
}

/// <summary>
/// Greedy Best First Search
/// </summary>
void GridGBFS::perform_search()
{
    priority_queue<StateGBFS, vector<StateGBFS>, greater<StateGBFS>> frontier;

    double heuristic_cost = heuristic(start);

    frontier.push({ start, heuristic_cost });

    came_from[start] = start;
    number_of_nodes++;

    if (using_GUI)
    {
        GUI_increment_instructions_sequence();
        GUI_set_text(start, heuristic_cost);
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
            if (came_from.find(next) == came_from.end())
            {
                heuristic_cost = heuristic(next);

                frontier.push({ next, heuristic_cost });

                came_from[next] = current;
                number_of_nodes++;


                if (using_GUI)
                {
                    GUI_set_text(next, heuristic_cost);
                    GUI_set_foreground(next, Color::Cyan);
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
