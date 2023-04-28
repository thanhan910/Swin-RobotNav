#pragma once
#include "GridInformed.h"
/// <summary>
/// A Star search
/// </summary>
class GridAS : public GridInformed
{
public:
	GridAS(const vector<vector<int>>& configs, bool using_jump_, bool using_gui_) : 
		GridInformed(configs, using_jump_, using_gui_) {};

	void perform_search() override;
};

