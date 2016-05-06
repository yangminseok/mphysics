#include "dem_simulation.h"

dem_simulation::dem_simulation()
	:simulation()
{

}

dem_simulation::dem_simulation(modeler *_md, grid_base* _gb)
	:simulation(_md, _gb)
{

}

dem_simulation::~dem_simulation()
{

}

bool dem_simulation::initilize()
{
	gb->allocMemory(md->numParticle());
}