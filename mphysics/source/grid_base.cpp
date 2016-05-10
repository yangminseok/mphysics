#include "grid_base.h"

VEC3F grid_base::wo;				// world origin
float grid_base::cs = 0.f;			// cell size
VEC3UI grid_base::gs;				// grid size

unsigned int* grid_base::sorted_id = NULL;
unsigned int* grid_base::cell_id = NULL;
unsigned int* grid_base::body_id = NULL;
unsigned int* grid_base::cell_start = NULL;
unsigned int* grid_base::cell_end = NULL;

grid_base::grid_base()
	: name("grid_base")
{

}

grid_base::grid_base(std::string _name, modeler* _md)
	: name(_name)
	, md(_md)
{

}

grid_base::~grid_base()
{
	clear();
}

void grid_base::clear()
{
	if (cell_id) delete[] cell_id; cell_id = NULL;
	if (body_id) delete[] body_id; body_id = NULL;
	if (sorted_id) delete[] sorted_id; sorted_id = NULL;
	if (cell_start) delete[] cell_start; cell_start = NULL;
	if (cell_end) delete[] cell_end; cell_end = NULL;
}

void grid_base::allocMemory(unsigned int n)
{
	ng = gs.x * gs.y * gs.z;
	cell_id = new unsigned int[n]; memset(cell_id, 0, sizeof(unsigned int)*n);
	body_id = new unsigned int[n]; memset(body_id, 0, sizeof(unsigned int)*n);
	sorted_id = new unsigned int[n]; memset(sorted_id, 0, sizeof(unsigned int)*n);
	cell_start = new unsigned int[ng]; memset(cell_start, 0, sizeof(unsigned int)*ng);
	cell_end = new unsigned int[ng]; memset(cell_end, 0, sizeof(unsigned int)*ng);
}

VEC3I grid_base::getCellNumber(float x, float y, float z)
{
	return VEC3I(
		static_cast<int>(abs(std::floor((x - wo.x) / cs))),
		static_cast<int>(abs(std::floor((y - wo.y) / cs))),
		static_cast<int>(abs(std::floor((z - wo.z) / cs)))
		);
}

unsigned int grid_base::getHash(VEC3I& c3)
{
	VEC3I gridPos;
	gridPos.x = c3.x & (gs.x - 1);
	gridPos.y = c3.y & (gs.y - 1);
	gridPos.z = c3.z & (gs.z - 1);
	return (gridPos.z*gs.y) * gs.x + (gridPos.y*gs.x) + gridPos.x;
}
