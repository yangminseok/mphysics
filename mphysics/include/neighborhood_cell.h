#ifndef NEIGHBORHOOD_CELL
#define NEIGHBORHOOD_CELL

#include "grid_base.h"

class neighborhood_cell : public grid_base
{
public:
	neighborhood_cell();
	neighborhood_cell(std::string _name);
	~neighborhood_cell();

	virtual void detection();
};

#endif