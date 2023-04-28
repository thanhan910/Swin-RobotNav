#pragma once

#include <utility>

using namespace std;

struct Location
{
    int x = -1, y = -1;

    bool is_null() const
    {
        return x < 0 && y < 0;
    }

    bool is_not_null() const
    {
        return !is_null();
    }

    void set_as_null()
    {
        x = -1; y = -1;
    }

    // Helpers for Location

    friend bool operator == (const Location& a, const Location& b)
    {
        return a.x == b.x && a.y == b.y;
    }

    friend bool operator != (const Location& a, const Location& b)
    {
        return !(a == b);
    }

    friend bool operator < (const Location& a, const Location& b)
    {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};

/* implement hash function so we can enque Location into an unordered set or map */
namespace std
{
    template <>
    struct hash<Location>
    {
        size_t operator()(const Location& id) const noexcept
        {
            return hash<int>()(id.x ^ (id.y << 16));
        }
    };
}
