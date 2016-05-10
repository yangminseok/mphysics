#ifndef COLLISION_H
#define COLLISION_H

#include <string>
#include "mphysics_types.h"
#include "modeler.h"
//class object;
//class particle_system;

class collision
{
public:
	collision();
	//collision(modeler* _md);
	//collision(modeler* _md, object* _iobj, object* _jobj);
	collision(std::string _name, modeler* _md);
	collision(const collision& cs);
	virtual ~collision();

//	modeler* model() const { return md; }
// 	object* object_i() const { return iobj; }
// 	object* object_j() const { return jobj; }
	void setContactParameter(float _rest, float _sratio, float _fric) { rest = _rest; sratio = _sratio; fric = _fric; }

	virtual bool collid(float dt) = 0;
	virtual bool collid_with_particle(unsigned int i, float dt) = 0;

	constant getConstant(float ir, float jr, float im, float jm, float iE, float jE, float ip, float jp);

protected:
	

	std::string name;

	float rest;
	float sratio;
	float fric;

	modeler* md;
};

#endif