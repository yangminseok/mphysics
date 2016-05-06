#ifndef MODELER_H
#define MODELER_H

#include "particle_system.h"
#include "cube.h"
#include "plane.h"
#include "collision.h"
#include <map>
//#include "object.h"

class modeler
{

public:
	modeler(std::string _name, tSimulation _sim);
	~modeler();

	void setParticleSystem(particle_system* _ps) { ps = _ps; }
	cube* makeCube(std::string _name, tMaterial _mat, tRoll _roll);
	plane* makePlane(std::string _name, tMaterial _mat, tRoll _roll);
	particle_system* makeParticleSystem(std::string _name);
	collision* makeCollision(std::string _name, std::string iobj, std::string jobj);

	unsigned int numParticle() { return ps->numParticle(); }

private:
	std::string name;
	tSimulation tsim;
	std::map<std::string, cube> cubes;
	std::map<std::string, plane> planes;
	std::map<std::string, collision> collisions;

	particle_system *ps;
};

#endif