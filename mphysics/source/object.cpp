#include "object.h"

unsigned int object::id = 0;

object::object(std::string& _name, tObject _tobj, tMaterial _mat, tRoll _roll)
	: name(_name)
	, obj_type(_tobj)
	, mat_type(_mat)
	, roll_type(_roll)
{
	id++;
	d = material::getDensity(mat_type);
	y = material::getYoungs(mat_type);
	p = material::getPoisson(mat_type);
}

object::object(const object& obj)
	: name(obj.objectName())
	, obj_type(obj.objectType())
	, mat_type(obj.materialType())
	, roll_type(obj.rolltype())
	, d(obj.density())
	, y(obj.youngs())
	, p(obj.poisson())
{

}

object::~object()
{

}