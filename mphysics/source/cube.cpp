#include "cube.h"

cube::cube(std::string _name, tMaterial _mat, tRoll _roll)
	: object(_name, CUBE, _mat, _roll)
{

}

cube::cube(const cube& _cube)
	: origin(_cube.min_point())
	, min_p(_cube.min_point())
	, max_p(_cube.max_point())
	, size(_cube.cube_size())
	, object(_cube)
{
	for (int i = 0; i < 6; i++){
		planes[i] = _cube.planes_data(i);
	}
}

cube::~cube()
{

}

bool cube::define(vector3<float>& min, vector3<float>& max)
{
	min_p = min;
	max_p = max;
	
	size.x = (max_p - vector3<float>(min_p.x, max_p.y, max_p.z)).length();
 	size.y = (max_p - vector3<float>(max_p.x, min_p.y, max_p.z)).length();
    size.z = (max_p - vector3<float>(max_p.x, max_p.y, min_p.z)).length();

	planes[0].define(min_p, min_p + vector3<float>(0, 0, size(2)), min_p + vector3<float>(size(0), 0, 0));
	planes[1].define(min_p, min_p + vector3<float>(0, size(1), 0), min_p + vector3<float>(0, 0, size(2)));
	planes[2].define(min_p + vector3<float>(size(0), 0, 0), min_p + vector3<float>(size(0), 0, size(2)), min_p + vector3<float>(size(0), size(1), 0));
	planes[3].define(min_p, min_p + vector3<float>(size(0), 0, 0), min_p + vector3<float>(0, size(1), 0));
	planes[4].define(min_p + vector3<float>(0, 0, size(2)), min_p + vector3<float>(0, size(1), size(2)), min_p + vector3<float>(size(0), 0, size(2)));
	planes[5].define(min_p + vector3<float>(0, size(1), 0), min_p + vector3<float>(size(0), size(1), 0), min_p + vector3<float>(0, size(1), size(2)));

	return true;
}

unsigned int cube::makeParticles(float rad, bool isOnlyCount, VEC3F_PTR pos)
{
	vector3<unsigned int> dim3np(
		 static_cast<unsigned int>(abs(size.x / (rad * 2)))
		,static_cast<unsigned int>(abs(size.y / (rad * 2)))
		,static_cast<unsigned int>(abs(size.z / (rad * 2))));

	float spacing = rad * 2.1f;
	unsigned int np = dim3np.x * dim3np.y * dim3np.z;
	if (!np)
		return NULL;
	if (isOnlyCount)
		return;
	srand(1976);
	float jitter = rad * 0.0001f;
	VEC3F_PTR pos = new VEC3F[np];
	unsigned int cnt = 0;
	for (unsigned int z = 0; z < dim3np.z; z++){
		for (unsigned int y = 0; y < dim3np.y; y++){
			for (unsigned int x = 0; x < dim3np.x; x++){
				float p[3] = { (min_p.x + rad + x * spacing) + frand()*jitter, (min_p.y + rad + y * spacing) + frand()*jitter, (min_p.z + rad + z * spacing) + frand()*jitter };
				if ((p[0] + rad) >= min_p.x + size.x || (p[1] + rad) >= min_p.y + size.y || (p[2] + rad) >= min_p.z + size.z)
					continue;

				pos[cnt].x = p[0];
				pos[cnt].y = p[1];
				pos[cnt].z = p[2];
			}
		}
	}
	return np;
}