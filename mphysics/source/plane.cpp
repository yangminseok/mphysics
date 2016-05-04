#include "plane.h"

plane::plane(std::string _name, tMaterial _mat, tRoll _roll)
	: object(_name, PLANE, _mat, _roll)
	, l1(0)
	, l2(0)
{

}

plane::plane(const plane& _plane)
	: object(_plane)
	, l1(_plane.L1())
	, l2(_plane.L2())
	, xw(_plane.XW())
	, uw(_plane.UW())
	, u1(_plane.U1())
	, u2(_plane.U2())
	, pa(_plane.PA())
	, pb(_plane.PB())
{
	
}

plane::~plane()
{

}

bool plane::define(vector3<float>& _xw, vector3<float>& _pa, vector3<float>& _pb)
{
	xw = _xw;
	pa = _pa;
	pb = _pb;

	pa -= xw;
	pb -= xw;
	l1 = pa.length();
	l2 = pb.length();
	u1 = pa / l1;
	u2 = pb / l2;
	uw = u1.cross(u2);
	return true;
}

VEC3F_PTR plane::makeParticles(float _rad)
{

}