#ifndef VELOCITY_VERLET_H
#define VELOCITY_VERLET_H

#include "integrator.h"

class velocity_verlet : public integrator
{
public:
	velocity_verlet();
	velocity_verlet(modeler *_md);
	~velocity_verlet();

	virtual void updatePosition(float dt);
	virtual void updateVelocity(float dt);
};

#endif