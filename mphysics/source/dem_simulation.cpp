#include "dem_simulation.h"
#include "collision.h"
#include <iomanip>
#include <boost/timer/timer.hpp>

dem_simulation::dem_simulation()
	:simulation()
{

}

dem_simulation::dem_simulation(modeler *_md, grid_base* _gb, integrator* _itor)
	:simulation(_md, _gb, _itor)
{

}

dem_simulation::~dem_simulation()
{

}

bool dem_simulation::initialize()
{
	gb->allocMemory(md->numParticle());
	md->closeStream();
	//object::close_stream();
	return true;
}

bool dem_simulation::saveResult(float ct, unsigned int p)
{
	std::fstream of;
	char partName[256] = { 0, };
	//double radius = 0.0;
	sprintf_s(partName, sizeof(char) * 256, "%s/part%04d.bin", md->modelPath().c_str(), p);

	of.write((char*)&ct, sizeof(float));
	of.write((char*)md->particleSystem()->position(), sizeof(VEC3F) * md->numParticle());
	of.write((char*)md->particleSystem()->velocity(), sizeof(VEC3F) * md->numParticle());
	of.close();
	return true;
}

void dem_simulation::collision_dem(float dt)
{
	md->particleSystem()->particleCollision(dt);
// 	std::map<std::string, collision*>::iterator c;
// 	for (c = md->collision_map().begin(); c != md->collision_map().end(); c++){
// 		c->second->collid(dt);
// 	}
}

bool dem_simulation::run(float et, float dt, unsigned int step)
{
	unsigned int part = 0;
	unsigned int cStep = 0;
	unsigned int eachStep = 0;
	unsigned int nStep = static_cast<unsigned int>((et / dt) + 1);
	float ct = dt * cStep;
	std::cout
		<< "-------------------------------------------------------------" << std::endl
		<< "| Num. Part | Sim. Time | I. Part | I. Total | Elapsed Time |" << std::endl
		<< "-------------------------------------------------------------" << std::endl;
	std::ios::right;
	std::setprecision(6);
	if (saveResult(ct, part)){
		std::cout << "| " << std::setw(9) << part << std::setw(12) << ct << std::setw(10) << eachStep << std::setw(11) << cStep << std::setw(15) << 0 << std::endl;
	}
	cStep++;	
	boost::timer::auto_cpu_timer t;
	while (cStep < nStep)
	{
		ct = dt * cStep;
		itor->updatePosition(dt);
		gb->detection();
		collision_dem(dt);
		itor->updateVelocity(dt);
		if (!((cStep) % step)){
			part++;
			if (saveResult(ct, part)){
				std::cout << "| " << std::setw(9) << part << std::setw(12) << ct << std::setw(10) << eachStep << std::setw(11) << cStep << std::setw(15) << 0 << std::endl;
			}
			eachStep = 0;
		}
		cStep++;
		eachStep++;
	}
	return true;
}