#include "particle_system.h"
#include "modeler.h"
#include "object.h"

particle_system::particle_system(std::string _name, modeler* _md)
	: name(_name)
	, md(_md)
	, max_r(0)
{
	md->setParticleSystem(this);
}

particle_system::~particle_system()
{
	clear();
}

void particle_system::clear()
{
	if (pos) delete[] pos; pos = NULL;
	if (vel) delete[] vel; vel = NULL;
	if (acc) delete[] acc; acc = NULL;
	if (omega) delete[] omega; omega = NULL;
	if (alpha) delete[] alpha; alpha = NULL;
	if (ms) delete[] ms; ms = NULL;
	if (iner) delete[] iner; iner = NULL;
	if (rad) delete[] rad; rad = NULL;
}

void particle_system::allocMemory(unsigned int _np)
{
	pos = new VEC3F[_np];
	vel = new VEC3F[_np];
	acc = new VEC3F[_np];
	omega = new VEC3F[_np];
	alpha = new VEC3F[_np];
	ms = new float[_np]; memset(ms, 0, sizeof(float)*_np);
	iner = new float[_np]; memset(iner, 0, sizeof(float)*_np);
	rad = new float[_np]; memset(rad, 0, sizeof(float)*_np);
}

bool particle_system::makeParticles(object *obj, float _rad)
{
	np = obj->makeParticles(_rad, false, NULL);
	allocMemory(np);
	obj->makeParticles(_rad, true, pos);
	rho = obj->density();
	E = obj->youngs();
	pr = obj->poisson();
	for (unsigned int i = 0; i < np; i++){
		rad[i] = _rad;
		if (max_r < rad[i])
			max_r = rad[i];
	}
	//pos = obj->makeParticles(_rad);
}