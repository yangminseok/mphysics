#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class plane : public object
{
public:
	plane(){}
	plane(std::string _name, tMaterial _mat, tRoll _roll);
	plane(const plane& _plane);
	~plane();

	virtual VEC3F_PTR makeParticles(float _rad);

	bool define(vector3<float>& _xw, vector3<float>& _pa, vector3<float>& _pb);
	float L1() const { return l1; }
	float L2() const { return l2; }
	vector3<float> U1() const { return u1; }
	vector3<float> U2() const { return u2; }
	vector3<float> UW() const { return uw; }
	vector3<float> XW() const { return xw; }
	vector3<float> PA() const { return pa; }
	vector3<float> PB() const { return pb; }

private:
	float l1, l2;
	vector3<float> u1;
	vector3<float> u2;
	vector3<float> uw;
	vector3<float> xw;
	vector3<float> pa;
	vector3<float> pb;
	
};

#endif