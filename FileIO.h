#pragma once
#include <vector>
#include <string>

using namespace std;

class FileIO
{
public:
	static vector<vector<int>> parse_file(char* filename);
};

