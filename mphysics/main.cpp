#include "mphysics.h"

int main(int argc, char** argv)
{
	modeler* md = new modeler("testModel", DEM);
	cube *pcube = md->makeCube("pCube", POLYETHYLENE, ROLL_PARTICLE);
    pcube->define(vector3<float>(-0.1f, -0.1f, -0.1f), vector3<float>(0.1f, 0.3f, 0.1f));

	plane *bound = md->makePlane("bPlane", tMaterial::ACRYLIC, ROLL_BOUNDARY);
	bound->define(vector3<float>(-1.0f, 0.0f, 1.0f), vector3<float>(1.0f, 0.0f, 1.0f), vector3<float>(-1.0f, 0.0f, -1.0f));

	particle_system *ps = new particle_system("particles");
	ps->makeParticles(pcube, 0.02);
}