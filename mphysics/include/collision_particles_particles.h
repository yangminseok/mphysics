#ifndef COLLISION_PARTICLES_PARTICLES_H
#define COLLISION_PARTICLES_PARTICLES_H

#include "particle_system.h"
#include "collision.h"

class collision_particles_particles : public collision
{
public:
	collision_particles_particles();
	collision_particles_particles(std::string _name, modeler* _md, particle_system* _ps);
	~collision_particles_particles();

	virtual bool collid(float dt);
	virtual bool collid_with_particle(unsigned int i, float dt) { return true; }

private:
	particle_system *ps;
};

#endif