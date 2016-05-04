#include "modeler.h"

modeler::modeler(std::string _name, tSimulation _sim)
	: name(_name)
	, tsim(_sim)
{

}

modeler::~modeler()
{

}

cube* modeler::makeCube(std::string _name, tMaterial _mat, tRoll _roll)
{
	cubes[_name] = cube(_name, _mat, _roll);
	return &(cubes.find(_name)->second);
}

plane* modeler::makePlane(std::string _name, tMaterial _mat, tRoll _roll)
{
	planes[_name] = plane(_name, _mat, _roll);
	return &(planes.find(_name)->second);
}