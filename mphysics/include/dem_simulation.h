#ifndef DEM_SIMULATION_H
#define DEM_SIMULATION_H

#include "simulation.h"

class dem_simulation : public simulation
{
public:
	dem_simulation();
	dem_simulation(modeler *_md, grid_base* _cb);
	~dem_simulation();

	virtual bool initilize();
};

#endif