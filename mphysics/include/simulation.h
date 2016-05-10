#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "modeler.h"
#include "grid_base.h"
#include "integrator.h"

class simulation
{
public:
	simulation();
	simulation(modeler* _md, grid_base *_gb, integrator* _iter);
	~simulation();

	modeler* model() { return md; }
	virtual bool initialize() = 0;
	virtual bool run(float et, float dt, unsigned int step) = 0;
	
protected:
	modeler* md;
	grid_base* gb;
	integrator* itor;
};

#endif