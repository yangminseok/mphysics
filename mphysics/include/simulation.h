#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "modeler.h"
#include "grid_base.h"

class simulation
{
public:
	simulation();
	simulation(modeler* _md, grid_base *_gb);
	~simulation();

	modeler* model() { return md; }
	virtual bool initilize() = 0;
	
protected:
	modeler* md;
	grid_base* gb;
};

#endif