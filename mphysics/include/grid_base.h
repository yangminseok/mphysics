#ifndef GRID_BASE_H
#define GRID_BASE_H

#include <iostream>
#include <string>
#include "mphysics_numeric.h"

class grid_base
{
public:
	grid_base();
	grid_base(std::string _name);
	virtual ~grid_base();

	void clear();
	virtual void detection() = 0;

	void setWorldOrigin(VEC3F _wo) { wo = _wo; }
	void setCellSize(float _cs) { cs = _cs; }
	void setGridSize(VEC3UI _gs) { gs = _gs; }

	void allocMemory(unsigned int n);

protected:
	std::string name;

	unsigned int* sorted_id;
	unsigned int* cell_id;
	unsigned int* body_id;
	unsigned int* cell_start;
	unsigned int* cell_end;

	VEC3F wo;			// world origin
	float cs;			// cell size
	VEC3UI gs;			// grid size
	unsigned int ng;	// the number of grid
};

#endif