#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include "mphysics_numeric.h"
#include <iostream>
#include <string>
#include <list>

class object;
class modeler;
class collision;

class particle_system
{
public:
	particle_system();
	particle_system(std::string _name, modeler *_md);
	~particle_system();

	void clear();
	VEC3F_PTR position() { return pos; }
	VEC3F_PTR velocity() { return vel; }
	VEC3F_PTR acceleration() { return acc; }
	VEC3F_PTR angVelocity() { return omega; }
	VEC3F_PTR angAcceleration() { return alpha; }
	VEC3F_PTR force() { return fr; }
	VEC3F_PTR moment() { return mm; }
	float* mass() { return ms; }
	float* inertia() { return iner; }
	float* radius() { return rad; }
	float maxRadius() { return max_r; }

	float density() { return rho; }
	float youngs() { return E; }
	float poisson() { return pr; }

	bool makeParticles(object *obj, float _rad);
	void setCollision(float _rest, float _sratio, float _fric);
	void addCollision(collision* c) { cs.push_back(c); }
	void allocMemory(unsigned int _np);
	unsigned int numParticle() { return np; }

	bool particleCollision(float dt);

private:
	std::string name;
	unsigned int np;
	float max_r;				// max radius

	VEC3F_PTR pos = NULL;
	VEC3F_PTR vel = NULL;
	VEC3F_PTR acc = NULL;
	VEC3F_PTR omega = NULL;
	VEC3F_PTR alpha = NULL;
	VEC3F_PTR fr = NULL;
	VEC3F_PTR mm = NULL;
	float* ms = NULL;
	float* iner = NULL;
	float* rad = NULL;

	float rho;
	float E;
	float pr;

	float rest;
	float sratio;
	float fric;

	collision *c_p2p;
	std::list<collision*> cs;
	modeler *md;
};

#endif