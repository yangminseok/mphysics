#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

template < typename T >
class vector3
{
public:
	vector3() : x(0), y(0), z(0) {}
	vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	vector3(T val) : x(val), y(val), z(val) {}
	vector3(T *ptr) : x(ptr[0]), y(ptr[1]), z(ptr[2]) {}
	vector3(const vector3& vec3) : x(vec3.x), y(vec3.y), z(vec3.z) {}
	~vector3() {}

	void zeros() { x = 0; y = 0; z = 0; }
	T length() { return sqrt(x*x + y*y + z*z); }
	T dot() { return x*x + y*y + z*z; }
	T dot(vector3& v3) { return x*v3.x + y*v3.y + z*v3.z; }
	T volume() { return x * y * z; }
	vector3 cross(vector3& v3) { return vector3(y*v3.z - z*v3.y, z*v3.x - x*v3.z, x*v3.y - y*v3.x); }

	vector3 operator+ (vector3& v3){ return vector3(x + v3.x, y + v3.y, z + v3.z); }
	template< typename T2 >
	vector3 operator- (vector3& v3) { return vector3(x - v3.x, y - v3.y, z - v3.z); }
	vector3 operator- (const vector3& v3) const{ return vector3(x - v3.x, y - v3.y, z - v3.z); }
	void operator-= (vector3& v3){ x -= v3.x; y -= v3.y; z -= v3.z; }
	void operator+= (vector3& v3){ x += v3.x; y += v3.y; z += v3.z; }
	vector3 operator- () { return vector3(-x, -y, -z); }
	vector3 operator/ (T val) { return vector3(x / val, y / val, z / val); }
	bool operator== (vector3& v3) { return (x == v3.x) && (y == v3.y) && (z == v3.z); }
	void operator*= (T val) { x *= val; y *= val; z *= val; }
	template< typename T1 >
	vector3 operator *(T1 val) { return vector3(val * x, val * y, val * z); }

	T& operator() (unsigned id){ return *((&x) + id); }

	vector3 normalize(){ return vector3(x, y, z) / length(); }

	T SignX() { return T(x <= 0 ? (x == 0 ? 0 : -1) : 1); }
	T SignY() { return T(y <= 0 ? (y == 0 ? 0 : -1) : 1); }
	T SignZ() { return T(z <= 0 ? (z == 0 ? 0 : -1) : 1); }
	vector3 Sign3() { return vector3(SignX(), SignY(), SignZ()); }

public:
	T x, y, z;
};

template< typename T >
std::ostream& operator<<(std::ostream& os, vector3<T>& v)
{
	std::ios::right;
	os << v.x << " " << v.y << " " << v.z;
	return os;
}


#endif