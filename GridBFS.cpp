#include "GridBFS.h"
#include <queue>

void GridBFS::perform_search()
{
    queue<Location> frontier;
    frontier.push(start);
    came_from[start] = start;
    number_of_nodes++;


    if (using_GUI)
    {
        GUI_increment_instructions_sequence();
        GUI_set_text(start, "0");
    }

    while (!frontier.empty())
    {
        Location current = frontier.front(); frontier.pop();

        if (using_GUI)
        {
            GUI_set_foreground(current, Color::Yellow);
        }

        if (is_goal(current))
        {
            set_goal_found(current);
            return;
        }

        GUI_increment_instructions_sequence();

        for (Location next : next_nodes(current))
        {
            if (came_from.find(next) == came_from.end())
            {
                frontier.push(next);
                came_from[next] = current;
                number_of_nodes++;


                if (using_GUI)
                {
                    GUI_set_foreground(next, Color::Cyan);
                    GUI_set_text(next, "0");
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
