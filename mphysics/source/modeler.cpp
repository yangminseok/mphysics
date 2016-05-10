#include "modeler.h"
#include "collision_particles_particles.h"
#include "collision_particles_plane.h"
#include <direct.h>

modeler::modeler(std::string _name, tSimulation _sim)
	: model_path(_name)
	, tsim(_sim)
{
	grav = VEC3F(0.f, -9.80665f, 0.f);
	int begin = model_path.find_last_of("/");
	name = model_path.substr(begin + 1, model_path.length());
	//std::fstream of;
	std::string model_file = model_path + "/" + name + ".mde";
	std::fstream check_model;
	check_model.open(model_file, std::ios::in);
	if (!check_model.is_open()){
		_mkdir(model_path.c_str());
	}
	check_model.close();
	io_model.open(model_file, std::ios::out);
	std::string mph_file = model_path + "/" + name + ".mph";
	io_mph.open(mph_file, std::ios::out);
}

modeler::~modeler()
{
	std::map<std::string, collision*>::iterator cs = collisions.begin();
	for (; cs != collisions.end(); cs++){
		delete cs->second;
	}

	if (io_model.is_open())
		io_model.close();
	if (io_mph.is_open())
		io_mph.close();
}

cube* modeler::makeCube(std::string _name, tMaterial _mat, tRoll _roll)
{
	cube cb(this, _name, _mat, _roll);
	cubes[_name] = cb;
	//cb.save_shape_data(io_model);
	return &(cubes.find(_name)->second);
}

plane* modeler::makePlane(std::string _name, tMaterial _mat, tRoll _roll)
{
	plane pe(this, _name, _mat, _roll);
	planes[_name] = pe;
	//pe.save_shape_data(io_model);
	return &(planes.find(_name)->second);
}

particle_system* modeler::makeParticleSystem(std::string _name)
{
	ps = new particle_system(_name, this);
	return ps;
}

// void modeler::saveModel()
// {
// 	//for (std::map<std::string, object)
// }

collision* modeler::makeCollision(std::string _name, float _rest, float _sratio, float _fric, tCollisionPair tcp, void* o1, void* o2)
{
	collision* c = NULL;
	switch (tcp){
	case PARTICLES_PARTICLES:
		c = new collision_particles_particles(_name, this, (particle_system*)o1);
		c->setContactParameter(_rest, _sratio, _fric);
		break;
	case PARTICLES_PLANE:
		particle_system *ps = (particle_system*)o1;
		c = new collision_particles_plane(_name, this, (particle_system*)o1, (plane*)o2);
		ps->addCollision(c);
		c->setContactParameter(_rest, _sratio, _fric);
		break;
	}

	if (c)
		collisions[_name] = c;
	
	return c;
}