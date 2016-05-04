#ifndef MODELER_H
#define MODELER_H

#include "particle_system.h"
#include "cube.h"
#include <map>
//#include "object.h"

class modeler
{

public:
	modeler(std::string _name, tSimulation _sim);
	~modeler();

	cube* makeCube(std::string _name, tMaterial _mat, tRoll _roll);
	plane* makePlane(std::string _name, tMaterial _mat, tRoll _roll);

private:
	std::string name;
	tSimulation tsim;
	std::map<std::string, cube> cubes;
	std::map<std::string, plane> planes;
};

#endif