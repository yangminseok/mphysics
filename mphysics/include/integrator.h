#ifndef INTEGRATOR_H
#define INTEGRATOR_H

class modeler;

class integrator
{
public:
	integrator();
	integrator(modeler* _md);
	virtual ~integrator();

	virtual void updatePosition(float dt) = 0;
	virtual void updateVelocity(float dt) = 0;

protected:
	modeler *md;
};

#endif