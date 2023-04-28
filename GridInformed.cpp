#include "GridInformed.h"

double GridInformed::heuristic(const Location& current, const Location& goal)
{
    return abs(goal.x - current.x) + abs(goal.y - current.y);
}

double GridInformed::heuristic(const Location& current)
{
    double result = -1;

    for (auto goal : goals)
    {
        double cost = heuristic(current, goal);

        if (result == -1 || result > cost)
        {
            result = cost;
        }
    }

    return result;
}
