#ifndef MPHYSICS_TYPES_H
#define MPHYSICS_TYPES_H

#define STEEL_YOUNGS_MODULUS 2e+011
#define STEEL_DENSITY 7850
#define STEEL_POISSON_RATIO 0.3

#define MEDIUM_CLAY_YOUNGS_MODULUS 35E+06
#define MEDIUM_CLAY_DENSITY 1900
#define MEDIUM_CLAY_POISSON_RATIO 0.45

#define POLYETHYLENE_YOUNGS_MODULUS 1.1E+9
#define POLYETHYLENE_DENSITY		950
#define POLYETHYLENE_POISSON_RATIO	0.42	

#define GLASS_YOUNGS_MODULUS	6.8e+10
#define GLASS_DENSITY		2180
#define GLASS_POISSON_RATIO	0.19

#define ACRYLIC_YOUNGS_MODULUS 3.2E+009
#define ACRYLIC_DENSITY			1185
#define ACRYLIC_POISSON_RATIO	0.37

#define ALUMINUM_YOUNGS_MODULUS  7.1E+10
#define ALUMINUM_DENSITY		2770
#define ALUMINUM_POISSON_RATIO	0.33

enum tMaterial { USER_INPUT = -1, NO_MATERIAL = 0, STEEL = 1, MEDIUM_CLAY = 2, POLYETHYLENE = 3, GLASS = 4, ACRYLIC = 5, ALUMINUM = 6 };
enum tRoll{ ROLL_BOUNDARY = 0, ROLL_PARTICLE, ROLL_MOVING };
enum tObject{ CUBE = 0, PLANE, PARTICLES };
enum tSimulation{ DEM, SPH, MBD };
enum tCollisionPair{ PARTICLES_PARTICLES, PARTICLES_PLANE };

typedef struct
{
	float kn, vn, ks, vs, mu;
}constant;

namespace material
{
// 	template<typename T>
// 	cMaterial<T> getMaterialCoefficient(Material t)
// 	{
// 		cMaterial<T> cm;
// 		cm.density = getDensity(t);
// 		cm.youngs = getYoungs(t);
// 		cm.poisson = getPoisson(t);
// 		return cm;
// 	}

	inline float getDensity(tMaterial t)
	{
		float v;
		switch (t)
		{
		case STEEL:			v = (float)STEEL_DENSITY;			break;
		case MEDIUM_CLAY:	v = (float)MEDIUM_CLAY_DENSITY;		break;
		case POLYETHYLENE:	v = (float)POLYETHYLENE_DENSITY;	break;
		case GLASS:			v = (float)GLASS_DENSITY;			break;
		case ACRYLIC:		v = (float)ACRYLIC_DENSITY;			break;
		case ALUMINUM:		v = (float)ALUMINUM_DENSITY;		break;
		}
		return v;
	}

	inline float getYoungs(tMaterial t)
	{
		float v;
		switch (t)
		{
		case STEEL:			v = (float)STEEL_YOUNGS_MODULUS;		break;
		case MEDIUM_CLAY:	v = (float)MEDIUM_CLAY_YOUNGS_MODULUS;	break;
		case POLYETHYLENE:	v = (float)POLYETHYLENE_YOUNGS_MODULUS;	break;
		case GLASS:			v = (float)GLASS_YOUNGS_MODULUS;		break;
		case ACRYLIC:		v = (float)ACRYLIC_YOUNGS_MODULUS;		break;
		case ALUMINUM:		v = (float)ALUMINUM_YOUNGS_MODULUS;		break;
		}
		return v;
	}

	inline float getPoisson(tMaterial t)
	{
		float v;
		switch (t)
		{
		case STEEL:			v = (float)STEEL_POISSON_RATIO;			break;
		case MEDIUM_CLAY:	v = (float)MEDIUM_CLAY_POISSON_RATIO;	break;
		case POLYETHYLENE:	v = (float)POLYETHYLENE_POISSON_RATIO;	break;
		case GLASS:			v = (float)GLASS_POISSON_RATIO;			break;
		case ACRYLIC:		v = (float)ACRYLIC_POISSON_RATIO;		break;
		case ALUMINUM:		v = (float)ALUMINUM_POISSON_RATIO;		break;
		}
		return v;
	}
}



#endif