#include "plane.h"
#include "modeler.h"

plane::plane(modeler *_md, std::string _name, tMaterial _mat, tRoll _roll)
	: object(_md, _name, PLANE, _mat, _roll)
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

bool plane::define(vector3<float>& _xw, vector3<float>& _pa, vector3<float>& _pb, bool isSave)
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
	
	if (isSave)
		save_shape_data();
	return true;
}

unsigned int plane::makeParticles(float _rad, bool isOnlyCount, VEC3F_PTR pos)
{
	return 0;
}

void plane::save_shape_data()
{
	md->modelStream() << "OBJECT RECTANGLE " << name << " " << roll_type << " " << mat_type << std::endl
		<< xw.x << " " << xw.y << " " << xw.z << std::endl;
	VEC3F ap = xw + l1 * u1;
	md->modelStream() << ap.x << " " << ap.y << " " << ap.z << std::endl;
	VEC3F cp = ap + l2 * u2;
	md->modelStream() << cp.x << " " << cp.y << " " << cp.z << std::endl;
	VEC3F bp = xw + l2 * u2;
	md->modelStream() << bp.x << " " << bp.y << " " << bp.z << std::endl;
	
}