#include "particle_system.h"
#include "modeler.h"
#include "object.h"
#include "collision.h"
#include "collision_particles_particles.h"
#include "grid_base.h"

particle_system::particle_system(std::string _name, modeler* _md)
	: name(_name)
	, md(_md)
	, max_r(0)
	, c_p2p(NULL)
{
	md->setParticleSystem(this);
}

particle_system::~particle_system()
{
	clear();
}

void particle_system::clear()
{
	if (pos) delete[] pos; pos = NULL;
	if (vel) delete[] vel; vel = NULL;
	if (acc) delete[] acc; acc = NULL;
	if (omega) delete[] omega; omega = NULL;
	if (alpha) delete[] alpha; alpha = NULL;
	if (ms) delete[] ms; ms = NULL;
	if (iner) delete[] iner; iner = NULL;
	if (rad) delete[] rad; rad = NULL;
	if (mm) delete[] mm; mm = NULL;
	if (ms) delete[] ms; ms = NULL;

	if (c_p2p) delete c_p2p; c_p2p = NULL;
}

void particle_system::allocMemory(unsigned int _np)
{
	pos = new VEC3F[_np];
	vel = new VEC3F[_np];
	acc = new VEC3F[_np];
	omega = new VEC3F[_np];
	alpha = new VEC3F[_np];
	fr = new VEC3F[_np];
	mm = new VEC3F[_np];
	ms = new float[_np]; memset(ms, 0, sizeof(float)*_np);
	iner = new float[_np]; memset(iner, 0, sizeof(float)*_np);
	rad = new float[_np]; memset(rad, 0, sizeof(float)*_np);
}

bool particle_system::makeParticles(object *obj, float _rad)
{
	np = obj->makeParticles(_rad, true, NULL);
	allocMemory(np);
	obj->makeParticles(_rad, false, pos);
	rho = obj->density();
	E = obj->youngs();
	pr = obj->poisson();
	for (unsigned int i = 0; i < np; i++){
		rad[i] = _rad;
		if (max_r < rad[i])
			max_r = rad[i];
		ms[i] = rho * 4.0f * (float)M_PI * pow(rad[i], 3.0f) / 3.0f;
		iner[i] = 2.0f * ms[i] * pow(rad[i], 2.0f) / 5.0f;
		fr[i] = ms[i] * md->gravity();
	}
	std::string file_par = md->modelPath() + "/" + md->modelName() + ".par";
	std::fstream io_par;
	io_par.open(file_par, std::ios::out);
	io_par.write((char*)pos, sizeof(VEC3F) * np);
	io_par.write((char*)vel, sizeof(VEC3F) * np);
	io_par.write((char*)rad, sizeof(float) * np);
	io_par.write((char*)ms, sizeof(float) * np);
	io_par.write((char*)iner, sizeof(float) * np);
	io_par.close();
//	md->makeCollision("collision_p2p", _rest, _sratio, _fric, NULL, NULL);
	return true;
}

void particle_system::setCollision(float _rest, float _sratio, float _fric)
{
	c_p2p = new collision_particles_particles("collision_particle_particle", md, this);
	c_p2p->setContactParameter(_rest, _sratio, _fric);
}

bool particle_system::particleCollision(float dt)
{
	//iE = jE = thisyoungs(); ip = jp = ps->poisson();
	VEC3I neigh, gp;
	float dist, cdist, mag_e, ds;
	unsigned int hash, sid, eid;
	constant c;
	VEC3F rp, u, rv, sf, sm, e, sh, shf;
	std::list<collision*>::iterator cc;
	for (unsigned int i = 0; i < np; i++){
		gp = grid_base::getCellNumber(pos[i].x, pos[i].y, pos[i].z);
		fr[i] = ms[i] * md->gravity();
		mm[i] = 0.0f;
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
							c = c_p2p->getConstant(rad[i], rad[k], ms[i], ms[k], E, E, pr, pr);
				
							rp = pos[k] - pos[i];
							dist = rp.length();
							cdist = (rad[i] + rad[k]) - dist;
							if (cdist > 0){
								u = rp / dist;
								rv = vel[k] + omega[k].cross(rad[k] * u) - (vel[i] + omega[i].cross(rad[i] * u));
								sf = (-c.kn * pow(cdist, 1.5f) + rv.dot(u) * c.vn) * u;
								e = rv - rv.dot(u) * u;
								mag_e = e.length();
								if (mag_e){
									sh = e / mag_e;
									ds = mag_e * dt;
									shf = min(c.ks * ds + c.vs * (rv.dot(sh)), c.mu * sf.length());
									sm = (rad[i] * u).cross(shf);
								}
								fr[i] += sf;
								mm[i] += sm;
							}
						}
					}
				}
			}
		}
		for (cc = cs.begin(); cc != cs.end(); cc++){
			(*cc)->collid_with_particle(i, dt);
		}
	}
	return true;
}