#include "collision.h"
//#include "grid_base.h"
//#include "collision_particles_plane.h"
#include <cmath>

collision::collision()
{

}

collision::collision(std::string _name, modeler *_md)
	: name(_name)
	, md(_md)
{

}

// collision::collision(modeler* _md)
// 	: md(_md)
// {
// 
// }

// collision::collision(modeler* _md, object* _iobj, object* _jobj)
// 	: md(_md)
// 	, iobj(_iobj)
// 	, jobj(_jobj)
// {
// 	
// }

collision::collision(const collision& cs)
// 	: iobj(cs.object_i())
// 	, jobj(cs.object_j())
// 	, md(cs.model())
{

}

collision::~collision()
{

}

constant collision::getConstant(float ir, float jr, float im, float jm, float iE, float jE, float ip, float jp)
{
// 	particle_system* ps = md->particleSystem();
	constant c = { 0, 0, 0, 0, 0 };
	float em = jm ? (im * jm) / (im + jm) : im;
	float er = jr ? (ir * jr) / (ir + jr) : ir;
	float eym = (iE * jE) / (iE*(1 - jp*jp) + jE*(1 - ip * ip));
	float beta = ((float)M_PI / log(rest));
	c.kn = (4.0f / 3.0f)*sqrt(er)*eym;
	c.vn = sqrt((4.0f*em * c.kn) / (1 + beta * beta));
	c.ks = c.kn * sratio;
	c.vs = c.vn * sratio;
	c.mu = fric;
 	return c;
}

// bool collision::collid_p2p(float dt)
// {
// 	particle_system *ps = md->particleSystem();
// 	iE = jE = ps->youngs(); ip = jp = ps->poisson();
// 	VEC3I neigh, gp;
// 	float im, jm, ir, jr, dist, cdist, mag_e, ds;
// 	unsigned int hash, sid, eid;
// 	constant c;
// 	VEC3F ipos, jpos, ivel, jvel, iomega, jomega, f, m, rp, u, rv, sf, sm, e, sh, shf;
// 	for (unsigned int i = 0; i < md->numParticle(); i++){
// 		ipos = ps->position()[i];
// 		ivel = ps->velocity()[i];
// 		iomega = ps->angVelocity()[i];
// 		gp = grid_base::getCellNumber(ipos.x, ipos.y, ipos.z);
// 		im = ps->mass()[i];
// 		ir = ps->radius()[i];
// 		f = im * md->gravity();
// 		m = 0.0f;
// 		for (int z = -1; z <= 1; z++){
// 			for (int y = -1; y <= 1; y++){
// 				for (int x = -1; x <= 1; x++){
// 					neigh = VEC3I(gp.x + x, gp.y + y, gp.z + z);
// 					hash = grid_base::getHash(neigh);
// 					sid = grid_base::cellStart(hash);
// 					if (sid != 0xffffffff){
// 						eid = grid_base::cellEnd(hash);
// 						for (unsigned int j = sid; j < eid; j++){
// 							unsigned int k = grid_base::sortedID(j);
// 							if (i == k || k >= md->numParticle())
// 								continue;
// 							jm = ps->mass()[k];
// 							jr = ps->radius()[k];
// 							c = getConstant(ir, jr, im, jm);
// 							jpos = ps->position()[k];
// 							jvel = ps->velocity()[k];
// 							jomega = ps->angVelocity()[k];
// 							rp = jpos - ipos;
// 							dist = rp.length();
// 							cdist = (ir + jr) - dist;
// 							if (cdist > 0){
// 								u = rp / dist;
// 								rv = jvel + jomega.cross(jr * u) - (ivel + iomega.cross(ir * u));
// 								sf = (-c.kn * pow(cdist, 1.5f) + rv.dot(u) * c.vn) * u;
// 								e = rv - rv.dot(u) * u;
// 								mag_e = e.length();
// 								if (mag_e){
// 									sh = e / mag_e;
// 									ds = mag_e * dt;
// 									shf = min(c.ks * ds + c.vs * (rv.dot(sh)), c.mu * sf.length());
// 									sm = (ir * u).cross(shf);
// 								}
// 								ps->force()[i] += sf;
// 								ps->moment()[i] += sm;
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return true;
// }

// bool collision::collid(float dt)
//{
//	if(!iobj && !jobj)
//		collid_p2p(dt);
//	if (iobj->objectType() == PLANE || jobj->objectType() == PLANE)
//		if (jobj == NULL){
//			collision_particle_plane(md->particleSystem(), dy
//		}
//
//	return true;
//}