#include "FileIO.h"
#include <regex>
#include <fstream>
#include <iostream>


/**
* Read the numbers in a line.
*/
vector<int> parse_line(string& line)
{
    vector<int> numbers;
    regex pattern(R"(\d+)");  // matches one or more digits

    for (sregex_iterator it(line.begin(), line.end(), pattern); it != sregex_iterator(); it++)
    {
        smatch match = *it;
        int number = stoi(match.str());  // convert string to int
        numbers.push_back(number);
    }

    return numbers;
}


/**
* Read the numbers in the file.
*/
vector<vector<int>> FileIO::parse_file(char* filename)
{
    ifstream input_file(filename);

    vector<vector<int>> configs;

    if (!input_file.is_open())
    {
        std::cout << "Could not open file " << filename << endl;
        return configs;
    }

    string line;

    vector<int> numbers;

    while (getline(input_file, line))
    {
        numbers = parse_line(line);

        configs.push_back(numbers);
    }

    input_file.close();

    return configs;
}
