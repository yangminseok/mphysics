#include "object.h"
#include "modeler.h"

unsigned int object::id = 0;
//std::ofstream object::io_object;

object::object(modeler* _md, std::string& _name, tObject _tobj, tMaterial _mat, tRoll _roll)
	: name(_name)
	, obj_type(_tobj)
	, mat_type(_mat)
	, roll_type(_roll)
	, md(_md)
{
	id++;
	d = material::getDensity(mat_type);
	y = material::getYoungs(mat_type);
	p = material::getPoisson(mat_type);

// 	if (io_object.is_open())
// 	{
// 		return;
// 	}
// 	std::string ofname = md->modelPath() + "/" + md->modelName() + ".ojt";
// 	io_object.open(ofname, std::ios::out);
// 	if (io_object.is_open())
// 	{
// 		return;
// 	}
	
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
// 	if (io_object.is_open())
// 		io_object.close();
}