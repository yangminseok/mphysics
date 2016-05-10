#ifndef CUBE_H
#define CUBE_H

#include "object.h"
#include "plane.h"

class cube : public object
{
public:
	cube(){}
	cube(modeler* _md, std::string _name, tMaterial _mat, tRoll _roll);
	cube(const cube& _cube);
	~cube();

	virtual unsigned int makeParticles(float rad, bool isOnlyCount, VEC3F_PTR pos = NULL);

	void save_shape_data();

	bool define(vector3<float>& min, vector3<float>& max);
	vector3<float> min_point() { return min_p; }
	vector3<float> min_point() const { return min_p; }
	vector3<float> max_point() { return max_p; }
	vector3<float> max_point() const { return max_p; }
	vector3<float> cube_size() { return size; }
	vector3<float> cube_size() const { return size; }
	plane planes_data(int i) const { return planes[i]; }

private:
	vector3<float> origin;
	vector3<float> min_p;
	vector3<float> max_p;
	vector3<float> size;
	plane planes[6];
};

#endif