#ifndef MPHYSICS_NUMERIC_H
#define MPHYSICS_NUMERIC_H

#include "vector3.hpp"

inline float frand() { return rand() / (float)RAND_MAX; }

typedef vector3<float>  VEC3F;
typedef vector3<unsigned int> VEC3UI;
typedef VEC3F* VEC3F_PTR;

#endif