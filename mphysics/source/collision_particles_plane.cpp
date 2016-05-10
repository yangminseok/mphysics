#include "collision_particles_plane.h"
#include "collision.h"

collision_particles_plane::collision_particles_plane()
{

}

collision_particles_plane::collision_particles_plane(std::string _name, modeler* _md, particle_system *_ps, plane *_p)
	: collision(_name, _md)
	, ps(_ps)
	, pe(_p)
{

}

collision_particles_plane::~collision_particles_plane()
{

}

bool collision_particles_plane::collid(float dt)
{
	float rad;
	VEC3F p, v, w, dp, wp;
	constant c;
	for (unsigned int i = 0; i < ps->numParticle(); i++){
		rad = ps->radius()[i];
		p = ps->position()[i];
		v = ps->velocity()[i];
		w = ps->angVelocity()[i];

		VEC3F sf, mf, mm;
		dp = p - pe->XW();
		wp = VEC3F(dp.dot(pe->U1()), dp.dot(pe->U2()), dp.dot(pe->UW()));
		c = getConstant(ps->radius()[i], 0.f, ps->mass()[i], 0.f, ps->youngs(), pe->youngs(), ps->poisson(), pe->poisson());
		if (abs(wp.z) < rad && (wp.x > 0 && wp.x < pe->L1()) && (wp.y > 0 && wp.y < pe->L2())){
			vector3<float> uu = pe->UW() / pe->UW().length();
			int pp = -sign(dp.dot(pe->UW()));
			vector3<float> unit = pp * uu;
			float collid_dist = rad - abs(dp.dot(unit));
			vector3<float> dv = -(v + w.cross(rad * unit));
			sf = (-c.kn * pow(collid_dist, 1.5f) + c.vn * dv.dot(unit)) * unit;
			vector3<float> e = dv - dv.dot(unit) * unit;
			float mag_e = e.length();
			if (mag_e){
				vector3<float> s_hat = e / mag_e;
				float ds = mag_e * dt;
				vector3<float> shear_force = min(c.ks * ds + c.vs * dv.dot(s_hat), c.mu * sf.length()) * s_hat;
				mm = (rad * unit).cross(shear_force);
			}
			mf = sf;
		}
		ps->force()[i] += mf;
		ps->moment()[i] += mm;
	}
	return true;
}

bool collision_particles_plane::collid_with_particle(unsigned int i, float dt)
{
	float rad = ps->radius()[i];
	VEC3F p = ps->position()[i];
	VEC3F v = ps->velocity()[i];
	VEC3F w = ps->angVelocity()[i];
	
	VEC3F sf, mf, mm;
	VEC3F dp = p - pe->XW();
	VEC3F wp = VEC3F(dp.dot(pe->U1()), dp.dot(pe->U2()), dp.dot(pe->UW()));
	constant c = getConstant(ps->radius()[i], 0.f, ps->mass()[i], 0.f, ps->youngs(), pe->youngs(), ps->poisson(), pe->poisson());
	if (abs(wp.z) < rad && (wp.x > 0 && wp.x < pe->L1()) && (wp.y > 0 && wp.y < pe->L2())){
		vector3<float> uu = pe->UW() / pe->UW().length();
		int pp = -sign(dp.dot(pe->UW()));
		vector3<float> unit = pp * uu;
		float collid_dist = rad - abs(dp.dot(unit));
		vector3<float> dv = -(v + w.cross(rad * unit));
		sf = (-c.kn * pow(collid_dist, 1.5f) + c.vn * dv.dot(unit)) * unit;
		vector3<float> e = dv - dv.dot(unit) * unit;
		float mag_e = e.length();
		if (mag_e){
			vector3<float> s_hat = e / mag_e;
			float ds = mag_e * dt;
			vector3<float> shear_force = min(c.ks * ds + c.vs * dv.dot(s_hat), c.mu * sf.length()) * s_hat;
			mm = (rad * unit).cross(shear_force);
		}
		mf = sf;
	}
	ps->force()[i] += mf;
	ps->moment()[i] += mm;
	return true;
}