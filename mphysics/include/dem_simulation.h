#ifndef DEM_SIMULATION_H
#define DEM_SIMULATION_H

#include "simulation.h"

class dem_simulation : public simulation
{
public:
	dem_simulation();
	dem_simulation(modeler *_md, grid_base* _cb, integrator* _itor);
	~dem_simulation();

	virtual bool initialize();
	virtual bool run(float et, float dt, unsigned int step);

private:
	bool saveResult(float ct, unsigned int p);
	void collision_dem(float dt);
};

#endif