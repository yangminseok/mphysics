#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "modeler.h"

class simulation
{
public:
	simulation();
	simulation(modeler* _md);
	~simulation();

	modeler* Modeler() { return md; }

	modeler* md;
};

#endif