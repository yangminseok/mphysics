#include "simulation.h"

simulation::simulation()
	: md(NULL)
	, gb(NULL)
	, itor(NULL)
{

}

simulation::simulation(modeler* _md, grid_base *_gb, integrator* _itor)
	: md(_md)
	, gb(_gb)
	, itor(_itor)
{
	md->closeStream();
}

simulation::~simulation()
{

}

