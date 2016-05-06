#ifndef COLLISION_H
#define COLLISION_H

#include <string>

class modeler;

class collision
{
public:
	collision();
	collision(modeler* _md);
	collision(modeler* _md, std::string _iobj, std::string _jobj);
	collision(const collision& cs);
	~collision();

	modeler* model() const { return md; }
	std::string object_i() const { return iobj; }
	std::string object_j() const { return jobj; }

private:
	std::string iobj;
	std::string jobj;

	modeler* md;
};

#endif