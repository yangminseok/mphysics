#include "simulation.h"

simulation::simulation()
	: md(NULL)
	, gb(NULL)
{

}

simulation::simulation(modeler* _md, grid_base *_gb)
	: md(_md)
	, gb(_gb)
{

}

simulation::~simulation()
{

}

