#pragma once
#include<vector>
#include <unordered_map>
#include <string>
#include "Location.h"
#include "Color.h"

using namespace std;


class Grid
{
// construtor
public:
    Grid(const vector<vector<int>>& configs, bool using_jump_ = false, bool using_gui_ = false);
    ~Grid();

// configurations
protected:
    bool using_GUI;
    bool using_jump;
    bool using_saving_next_cells = false;

// width, height of grid
private:
    int width, height;
    bool is_in_bounds(const Location& id) const;

// grid walls
private:
    vector<pair<Location, Location>> walls;
    void add_wall(int x, int y, int w, int h);
    bool is_wall(const Location& id) const;
    unordered_map<Location, vector<Location>> next_nodes_map;

// node neighbors
private:
    static const Location D_NEIGHBORS[4];

protected:
    vector<Location> next_nodes(const Location& id);
    size_t cost(const Location& current, const Location& next) const;

// initial state
protected:
    Location start;

// Goals
protected:
    vector<Location> goals;
    bool is_goal(const Location& id) const;
private:
    void add_goal(int x, int y);

// Final goal found
private:
    Location goal_final;
    vector<Location> path;
protected:
    bool is_goal_found() const;
    void set_goal_found(const Location& goal_found_);

// Search
protected:
    unordered_map<Location, Location> came_from;
    void construct_path();
public:
    size_t number_of_nodes = 0;
    int get_number_of_nodes();
    virtual void perform_search() = 0;
    void print_path();

// GUI
private:
    struct GUI_Cell
    {
        int foreground = -1;
        int background = -1;
        string text;
    };

    struct GUI_Instructions
    {
        Location loc;
        GUI_Cell cell;
    };

    int GUI_cell_size = 1;
    GUI_Cell** GUI_Grid;
    vector<vector<GUI_Instructions>> GUI_instructions_sequence;
    void GUI_init_grid();
    void GUI_draw_grid();
    void GUI_draw_search(bool step_by_step, int delay_miliseconds);
    void GUI_draw_path(bool step_by_step, int delay_miliseconds);

protected:
    void GUI_increment_instructions_sequence();
    void GUI_set_background(const Location& id, Color col);
    void GUI_set_foreground(const Location& id, Color col);
    void GUI_set_text(const Location& id, string text);
    void GUI_set_text(const Location& id, double text);
    void GUI_set_text(const Location& id, int text);
public:
    void GUI_draw(bool step_by_step = false, int delay_miliseconds = 200);
};

