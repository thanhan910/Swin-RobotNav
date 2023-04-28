#include <iostream>
#include <unordered_set>
#include <chrono>

#include "FileIO.h"

#include "Grid.h"

#include "Factory.h"

using namespace std;

const unordered_set<string> METHODS{ "DFS", "BFS", "GBFS", "AS", "CUS1", "CUS2" };

const int LOOP_COUNT = 100;
const string METHOD_ALL = "all";

string filename;
string method;
bool using_jump;
bool using_GUI;
bool using_measure_time;
bool using_loop;
vector<vector<int>> configs;

void run(const string& method)
{
    int count = 1;
    long double avg_duration = 0;
    if (using_loop)
    {
        count = LOOP_COUNT;
    }

    cout << filename << " " << method << " ";

    // Initialize grid and the search program
    Grid* grid = Factory::createGrid(method, configs, using_jump, using_GUI);

    // Perform search

    auto start = std::chrono::high_resolution_clock::now();

    grid->perform_search();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << grid->get_number_of_nodes() << endl;
    grid->print_path();

    if (using_measure_time)
    {
        cout << "Execution time: " << duration << " ns" << endl;
    }

    if (using_loop)
    {
        while (count--)
        {
            delete grid;

            // Initialize grid and the search program
            grid = Factory::createGrid(method, configs, using_jump, using_GUI);

            // Perform search

            start = std::chrono::high_resolution_clock::now();

            grid->perform_search();

            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            avg_duration += (long double)duration / LOOP_COUNT;
        }

        cout << "Average execution time after " << LOOP_COUNT << " loops: " << avg_duration << " ns" << endl;
    }

    if (using_GUI)
    {
        char c;
        cout << "Enter 'y' if you want to explore step by step: ";
        cin >> c;
        grid->GUI_draw(c == 'y');
    }

    delete grid;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Command should be: " << argv[0] << " <filename> <method>\n";
        return 0;
    }

    // Open and read file
    configs = FileIO::parse_file(argv[1]);

    if (configs.size() < 3)
    {
        if (configs.size() > 0)
        {
            cout << "There should be at least 3 lines in file " << argv[1] << endl;
        }
        
        return 0;
    }

    filename = argv[1];

    method = argv[2];

    if (!METHODS.count(method) && method != METHOD_ALL)
    {
        cout << "The method " << method << " does not exist. Please use methods: DFS, BFS, GBFS, AS, CUS1, CUS2" << endl;
        return 0;
    }


    // Check if there are additional arguments
    unordered_set<string> options;

    for (int i = 3; i < argc; i++)
    {
        options.insert(argv[i]);
    }

    using_jump = options.count("jump");
    using_GUI = options.count("GUI");
    using_measure_time = options.count("time");
    using_loop = options.count("loop");

    
    if (method == METHOD_ALL)
    {
        for (const auto& method_ : METHODS)
        {
            run(method_);
        }
    }
    else
    {
        run(method);
    }

    return 0;
}
