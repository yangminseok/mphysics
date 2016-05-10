#ifndef COLLISION_PARTICLES_PLANE_H
#define COLLISION_PARTICLES_PLANE_H

#include "particle_system.h"
#include "plane.h"
#include "collision.h"

class collision_particles_plane : public collision
{
public:
	collision_particles_plane();
	collision_particles_plane(std::string _name, modeler* _md, particle_system *_ps, plane *_p);
	~collision_particles_plane();

	virtual bool collid(float dt);
	virtual bool collid_with_particle(unsigned int i, float dt);

private:
	particle_system *ps;
	plane *pe;
};

#endif