#include "collision.h"

collision::collision()
{

}

collision::collision(modeler* _md)
	: md(_md)
{

}

collision::collision(modeler* _md, std::string _iobj, std::string _jobj)
	: md(_md)
	, iobj(_iobj)
	, jobj(_jobj)
{
	
}

collision::collision(const collision& cs)
	: iobj(cs.object_i())
	, jobj(cs.object_j())
	, md(cs.model())
{

}

collision::~collision()
{

}