#ifndef GRID_BASE_H
#define GRID_BASE_H

#include <iostream>
#include <string>
#include "mphysics_numeric.h"

class modeler;

class grid_base
{
public:
	grid_base();
	grid_base(std::string _name, modeler* _md);
	virtual ~grid_base();

	void clear();
	virtual void detection() = 0;

	void setWorldOrigin(VEC3F _wo) { wo = _wo; }
	void setCellSize(float _cs) { cs = _cs; }
	void setGridSize(VEC3UI _gs) { gs = _gs; }

	void allocMemory(unsigned int n);

	static VEC3I getCellNumber(float x, float y, float z);
	static unsigned int getHash(VEC3I& c3);
	static unsigned int sortedID(unsigned int id) { return sorted_id[id]; }
	static unsigned int cellID(unsigned int id) { return cell_id[id]; }
	static unsigned int bodyID(unsigned int id) { return body_id[id]; }
	static unsigned int cellStart(unsigned int id) { return cell_start[id]; }
	static unsigned int cellEnd(unsigned int id) { return cell_end[id]; }

protected:
	std::string name;

	static unsigned int* sorted_id;
	static unsigned int* cell_id;
	static unsigned int* body_id;
	static unsigned int* cell_start;
	static unsigned int* cell_end;

	static VEC3F wo;			// world origin
	static float cs;			// cell size
	static VEC3UI gs;			// grid size
	unsigned int ng;	// the number of grid

	modeler *md;
};

#endif