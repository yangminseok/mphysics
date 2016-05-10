#include "mphysics.h"

std::string case_dir = "C:/mphysics/case/testModel";

int main(int argc, char** argv)
{
	modeler* md = new modeler(case_dir, DEM);
	cube *pcube = md->makeCube("pCube", POLYETHYLENE, ROLL_PARTICLE);
    pcube->define(vector3<float>(-0.1f, 0.1f, -0.1f), vector3<float>(0.1f, 0.3f, 0.1f));

	plane *bound = md->makePlane("bPlane", tMaterial::ACRYLIC, ROLL_BOUNDARY);
	bound->define(vector3<float>(-1.0f, 0.0f, 1.0f), vector3<float>(1.0f, 0.0f, 1.0f), vector3<float>(-1.0f, 0.0f, -1.0f));

	particle_system *ps = md->makeParticleSystem("ps");
	ps->makeParticles(pcube, 0.09f);
	ps->setCollision(0.7f, 0.8f, 0.3f);
	//ps->makeCollision()
	//collision *c1 = md->makeCollision("collision_p2p", 0.7f, 0.8f, 0.3f, PARTICLES_PARTICLES, ps);
	collision *c2 = md->makeCollision("collision_bound", 0.98f, 0.8f, 0.3f, PARTICLES_PLANE, ps, bound);
	//collision *c2 = md->makeCollision("collision_p2bound", 0.98f, 0.8f, 0.3f, bound, NULL);

	neighborhood_cell *neigh = new neighborhood_cell("detector", md);
	neigh->setWorldOrigin(VEC3F(-0.2f, 0.0f, -0.2f));
	neigh->setGridSize(VEC3UI(128, 128, 128));
	neigh->setCellSize(ps->maxRadius() * 2.0f);

	velocity_verlet *vv = new velocity_verlet(md);

	simulation *sim = new dem_simulation(md, neigh, vv);

	sim->initialize();

	sim->run(1.0f, 1e-5f, 1000);

	delete md;
	delete neigh;
	delete vv;
}