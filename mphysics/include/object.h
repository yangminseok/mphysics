#ifndef OBJECT_H
#define OBJECT_H

#include "mphysics_types.h"
#include "mphysics_numeric.h"
#include <fstream>
#include <string>

class modeler;

class object
{
public:
	object(){}
	object(modeler *_md, std::string &_name, tObject _tobj, tMaterial _mat, tRoll _roll);
	object(const object& obj);
	virtual ~object();

	virtual unsigned int makeParticles(float rad, bool isOnlyCount, VEC3F_PTR pos = NULL) = 0;

	unsigned int ID() { return id; }
	//virtual void saveResult(std::fstream& of) = 0;
	std::string objectName() const { return name; }
	tObject objectType() const { return obj_type; }
	tMaterial materialType() const { return mat_type; }
	tRoll rolltype() const { return roll_type; }

	float density() const { return d; }
	float youngs() const { return y; }
	float poisson() const { return p; }

	//static void close_stream() { io_object.close(); }

protected:
	static unsigned int id;

	//static std::ofstream io_object;

	std::string name;
	tRoll roll_type;
	tObject obj_type;
	tMaterial mat_type;
	float d;
	float y;
	float p;
	//simulation *sim;
	modeler* md;
};

#endif