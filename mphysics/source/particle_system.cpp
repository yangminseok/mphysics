#include "particle_system.h"
#include "object.h"

particle_system::particle_system(std::string _name)
	: name(_name)
{

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

bool particle_system::makeParticles(object *obj, float _rad)
{
	pos = obj->makeParticles(_rad);
}