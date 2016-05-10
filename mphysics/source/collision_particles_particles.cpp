#include "collision_particles_particles.h"
#include "grid_base.h"

collision_particles_particles::collision_particles_particles()
{

}

collision_particles_particles::collision_particles_particles(std::string _name, modeler* _md, particle_system* _ps)
	: collision(_name, _md)
	, ps(_ps)
{

}

collision_particles_particles::~collision_particles_particles()
{

}

bool collision_particles_particles::collid(float dt)
{
	//iE = jE = ps->youngs(); ip = jp = ps->poisson();
	VEC3I neigh, gp;
	float im, jm, ir, jr, dist, cdist, mag_e, ds;
	unsigned int hash, sid, eid;
	constant c;
	VEC3F ipos, jpos, ivel, jvel, iomega, jomega, f, m, rp, u, rv, sf, sm, e, sh, shf;
	for (unsigned int i = 0; i < ps->numParticle(); i++){
		ipos = ps->position()[i];
		ivel = ps->velocity()[i];
		iomega = ps->angVelocity()[i];
		gp = grid_base::getCellNumber(ipos.x, ipos.y, ipos.z);
		im = ps->mass()[i];
		ir = ps->radius()[i];
		f = im * md->gravity();
		m = 0.0f;
		for (int z = -1; z <= 1; z++){
			for (int y = -1; y <= 1; y++){
				for (int x = -1; x <= 1; x++){
					neigh = VEC3I(gp.x + x, gp.y + y, gp.z + z);
					hash = grid_base::getHash(neigh);
					sid = grid_base::cellStart(hash);
					if (sid != 0xffffffff){
						eid = grid_base::cellEnd(hash);
						for (unsigned int j = sid; j < eid; j++){
							unsigned int k = grid_base::sortedID(j);
							if (i == k || k >= md->numParticle())
								continue;
							jm = ps->mass()[k];
							jr = ps->radius()[k];
							c = getConstant(ir, jr, im, jm, ps->youngs(), ps->youngs(), ps->poisson(), ps->poisson());
							jpos = ps->position()[k];
							jvel = ps->velocity()[k];
							jomega = ps->angVelocity()[k];
							rp = jpos - ipos;
							dist = rp.length();
							cdist = (ir + jr) - dist;
							if (cdist > 0){
								u = rp / dist;
								rv = jvel + jomega.cross(jr * u) - (ivel + iomega.cross(ir * u));
								sf = (-c.kn * pow(cdist, 1.5f) + rv.dot(u) * c.vn) * u;
								e = rv - rv.dot(u) * u;
								mag_e = e.length();
								if (mag_e){
									sh = e / mag_e;
									ds = mag_e * dt;
									shf = min(c.ks * ds + c.vs * (rv.dot(sh)), c.mu * sf.length());
									sm = (ir * u).cross(shf);
								}
								ps->force()[i] += sf;
								ps->moment()[i] += sm;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
