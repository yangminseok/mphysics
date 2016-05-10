#ifndef MPHYSICS_NUMERIC_H
#define MPHYSICS_NUMERIC_H

#include "vector3.hpp"

#define min(a,b) a < b ? a : b
#define max(a,b) a > b ? a : b

#define sign(a) a <= 0 ? (a == 0 ? 0 : -1) : 1

inline float frand() { return rand() / (float)RAND_MAX; }

typedef vector3<float>			VEC3F;
typedef vector3<int>			VEC3I;
typedef vector3<unsigned int>	VEC3UI;
typedef VEC3F*					VEC3F_PTR;

#endif