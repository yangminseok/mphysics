#ifndef OBJECT_H
#define OBJECT_H

#include "mphysics_types.h"
#include "mphysics_numeric.h"
#include <fstream>
#include <string>

//class simulation;

class object
{
public:
	object(){}
	object(std::string &_name, tObject _tobj, tMaterial _mat, tRoll _roll);
	object(const object& obj);
	~object();

	virtual VEC3F_PTR makeParticles(float rad) = 0;

	unsigned int ID() { return id; }
	//virtual void saveResult(std::fstream& of) = 0;
	std::string objectName() const { return name; }
	tObject objectType() const { return obj_type; }
	tMaterial materialType() const { return mat_type; }
	tRoll rolltype() const { return roll_type; }

	float density() const { return d; }
	float youngs() const { return y; }
	float poisson() const { return p; }

protected:
	static unsigned int id;

	std::string name;
	tRoll roll_type;
	tObject obj_type;
	tMaterial mat_type;
	float d;
	float y;
	float p;
	//simulation *sim;
};

#endif