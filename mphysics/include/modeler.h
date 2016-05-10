#ifndef MODELER_H
#define MODELER_H

#include "particle_system.h"
#include "cube.h"
#include "plane.h"
#include <map>
#include <fstream>
//#include "object.h"

class collision;
class collision_particles_particles;
class collision_particles_plane;

class modeler
{

public:
	modeler(std::string _name, tSimulation _sim);
	~modeler();

	void setParticleSystem(particle_system* _ps) { ps = _ps; }
	cube* makeCube(std::string _name, tMaterial _mat, tRoll _roll);
	plane* makePlane(std::string _name, tMaterial _mat, tRoll _roll);
	particle_system* makeParticleSystem(std::string _name);
	collision* makeCollision(std::string _name, float _rest, float _sratio, float _fric, tCollisionPair tcp, void *o1, void *o2 = NULL);
	//collision_particles_plane* make_collision_ps_plane(std::string _name, float _rest, float _sratio, float _)


	unsigned int numParticle() { return ps->numParticle(); }
	std::string& modelPath() { return model_path; }
	std::string& modelName() { return name; }
	particle_system* particleSystem() { return ps; }
	std::map<std::string, collision*>& collision_map() { return collisions; }
	VEC3F gravity() { return grav; }

	std::fstream& modelStream() { return io_model; }
	std::fstream& mphysicsStream() { return io_mph; }
	void closeStream() { io_model.close(); io_mph.close(); }

private:
	VEC3F grav;

	std::fstream io_model;
	std::fstream io_mph;
	std::string model_path;
	std::string name;
	tSimulation tsim;
	std::map<std::string, cube> cubes;
	std::map<std::string, plane> planes;
	std::map<std::string, collision*> collisions;

	particle_system *ps;
};

#endif