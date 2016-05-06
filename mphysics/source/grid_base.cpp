#include "grid_base.h"

grid_base::grid_base()
	: sorted_id(NULL)
	, cell_id(NULL)
	, body_id(NULL)
	, cell_start(NULL)
	, cell_end(NULL)
	, name("grid_base")
{

}

grid_base::grid_base(std::string _name)
	: sorted_id(NULL)
	, cell_id(NULL)
	, body_id(NULL)
	, cell_start(NULL)
	, cell_end(NULL)
	, name(_name)
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
	cell_id = new unsigned int[n]; memset(cell_id, 0, sizeof(unsigned int)*n);
	body_id = new unsigned int[n]; memset(body_id, 0, sizeof(unsigned int)*n);
	sorted_id = new unsigned int[n]; memset(sorted_id, 0, sizeof(unsigned int)*n);
	cell_start = new unsigned int[ng]; memset(cell_start, 0, sizeof(unsigned int)*ng);
	cell_end = new unsigned int[ng]; memset(cell_end, 0, sizeof(unsigned int)*ng);
}