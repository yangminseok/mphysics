#include "mphysics.h"

int main(int argc, char** argv)
{
	modeler* md = new modeler("testModel", DEM);
	cube *pcube = md->makeCube("pCube", POLYETHYLENE, ROLL_PARTICLE);
    pcube->define(vector3<float>(-0.1f, -0.1f, -0.1f), vector3<float>(0.1f, 0.3f, 0.1f));

	plane *bound = md->makePlane("bPlane", tMaterial::ACRYLIC, ROLL_BOUNDARY);
	bound->define(vector3<float>(-1.0f, 0.0f, 1.0f), vector3<float>(1.0f, 0.0f, 1.0f), vector3<float>(-1.0f, 0.0f, -1.0f));

	particle_system *ps = md->makeParticleSystem("ps");
	ps->makeParticles(pcube, 0.02);

	collision *c1 = md->makeCollision("collision_p2p", "ps", "ps");
	collision *c2 = md->makeCollision("collision_p2bound", "ps", "bPlane");

	neighborhood_cell *neigh = new neighborhood_cell("detector");
	neigh->setWorldOrigin(VEC3F(-0.2f, 0.0f, -0.2f));
	neigh->setGridSize(VEC3UI(128, 128, 128));
	neigh->setCellSize(ps->maxRadius() * 2.0f);

	simulation *sim = new dem_simulation(md, neigh);

	sim->initialize();

	delete md;
	delete neigh;
}