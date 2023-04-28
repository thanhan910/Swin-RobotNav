#include "Grid.h"
#include <iostream>
#include <thread>

void Grid::GUI_increment_instructions_sequence()
{
    GUI_instructions_sequence.push_back(vector<GUI_Instructions>());
}

void Grid::GUI_set_foreground(const Location& id, Color col)
{
    if (GUI_instructions_sequence.empty()) GUI_increment_instructions_sequence();

    GUI_Cell cell;

    cell.foreground = col;

    GUI_instructions_sequence.back().push_back({ id, cell });
}

void Grid::GUI_set_background(const Location& id, Color col)
{
    if (GUI_instructions_sequence.empty()) GUI_increment_instructions_sequence();

    GUI_Cell cell;

    cell.background = col;

    GUI_instructions_sequence.back().push_back({ id, cell });
}

void Grid::GUI_set_text(const Location& id, string text)
{
    if (GUI_instructions_sequence.empty()) GUI_increment_instructions_sequence();

    if (text.size() > GUI_cell_size) GUI_cell_size = text.size();

    GUI_Cell cell;

    cell.text = text;

    GUI_instructions_sequence.back().push_back({ id, cell });
}

void Grid::GUI_set_text(const Location& id, double text)
{
    GUI_set_text(id, (int)text);
}

void Grid::GUI_set_text(const Location& id, int text)
{
    GUI_set_text(id, to_string(text));
}


// Function to set console color
void setConsoleColor(int colorCode)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, colorCode);
}

// Function to set console color
void setConsoleColor(int text_color, int background_color)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, text_color | background_color);
}

// reset the console text color to its default value
void resetConsoleColor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, Color::White | Color::Black);
}


// Draw text on the console, expand the text to max size length by adding trailing spaces
// so that the cells have equal spaces
void console_draw(string text, int max_size, int text_color, int background_color)
{
    if (text_color >= 0 && background_color >= 0)
    {
        setConsoleColor(text_color, background_color);
    }
    else if (text_color < 0 && background_color >= 0)
    {
        setConsoleColor(background_color);
    }
    else if (text_color >= 0 && background_color < 0)
    {
        setConsoleColor(text_color);
    }
    cout << text;
    for (int i = max_size; i > text.size(); i--) cout << " ";
}

// Create a 2D array to store the cell colors and text
void Grid::GUI_init_grid()
{
    GUI_Grid = new GUI_Cell * [height];
    for (int row = 0; row < height; row++)
    {
        GUI_Grid[row] = new GUI_Cell[width];
        for (int col = 0; col < width; col++)
        {
            GUI_Grid[row][col].foreground = Color::White;
            GUI_Grid[row][col].text = ".";
        }
    }

    GUI_Grid[start.y][start.x].background = Color::BackgroundRed;
    GUI_Grid[start.y][start.x].text = "I";

    for (auto goal : goals)
    {
        GUI_Grid[goal.y][goal.x].background = Color::BackgroundGreen;
        GUI_Grid[goal.y][goal.x].text = "G";
    }

    for (auto wall : walls)
    {
        for (int x = wall.first.x; x <= wall.second.x; x++)
        {
            for (int y = wall.first.y; y <= wall.second.y; y++)
            {
                GUI_Grid[y][x].background = Color::BackgroundGrey;
                GUI_Grid[y][x].text = "W";
            }
        }
    }
}

// Draw the grid from the stored 2D array
void Grid::GUI_draw_grid()
{
    // Update the grid
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            GUI_Cell* cell = &GUI_Grid[row][col];
            console_draw(cell->text, GUI_cell_size, cell->foreground, cell->background);
            resetConsoleColor();
            cout << ' ';
        }
        cout << "\n\n";
    }
}

void Grid::GUI_draw_path(bool step_by_step, int delay_miliseconds)
{
    construct_path();

    for (int i = 1; i < path.size() - 1; i++)
    {
        std::system("cls"); // Clear console screen

        // Update the cell color and text

        GUI_Grid[path[i].y][path[i].x].background = Color::BackgroundYellow;

        GUI_draw_grid();

        if (step_by_step)
        {
            cout << "Press any key to continue....";
            cin.get();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_miliseconds));
        }
    }
}

void Grid::GUI_draw_search(bool step_by_step, int delay_miliseconds)
{
    // Maximum duration to continously display the searching procedure is 60 seconds
    int min_delay = (double)60000 / GUI_instructions_sequence.size();
    if (min_delay < delay_miliseconds) delay_miliseconds = min_delay;
    
    for (auto configs : GUI_instructions_sequence)
    {
        // Update the cell color and text
        for (auto config : configs)
        {

            GUI_Cell* cell = &GUI_Grid[config.loc.y][config.loc.x];

            if (!config.cell.text.empty())
            {
                cell->text = config.cell.text;
            }

            if (config.cell.foreground >= 0)
            {
                cell->foreground = config.cell.foreground;
            }

            if (config.cell.background >= 0)
            {
                cell->background = config.cell.background;
            }
        }
        std::system("cls"); // Clear console screen
        GUI_draw_grid();


        if (step_by_step)
        {
            cout << "Press any key to continue....";
            cin.get();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_miliseconds));
        }
    }
}

void Grid::GUI_draw(bool step_by_step, int delay_miliseconds)
{

    GUI_init_grid();

    if (step_by_step)
    {
        cout << "Press any key to continue....";
        cin.get();
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_miliseconds));
    }

    // Print search sequence based on the saved instructions
    GUI_draw_search(step_by_step, delay_miliseconds);

    // Draw path
    GUI_draw_path(step_by_step, delay_miliseconds);

    // Print result
    cout << "Number of nodes: " << get_number_of_nodes() << endl;
    print_path();

    // Free memory used by the grid
    for (int row = 0; row < height; row++)
    {
        delete[] GUI_Grid[row];
    }
    delete[] GUI_Grid;

    resetConsoleColor();

    cout << "Press any key to exit GUI..."; cin.get();
}