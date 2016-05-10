#include "neighborhood_cell.h"
#include "modeler.h"
#include "thrust/sort.h"

neighborhood_cell::neighborhood_cell()
	: grid_base()
{

}

neighborhood_cell::neighborhood_cell(std::string _name, modeler* _md)
	: grid_base(_name, _md)
{

}

neighborhood_cell::~neighborhood_cell()
{

}

void neighborhood_cell::reorderDataAndFindCellStart(unsigned int id, unsigned int begin, unsigned int end)
{
	cell_start[id] = begin;
	cell_end[id] = end;
	unsigned dim = 0, bid = 0;
	for (unsigned i(begin); i < end; i++){
		sorted_id[i] = body_id[i];
	}
}

void neighborhood_cell::detection()
{
	VEC3F_PTR pos = md->particleSystem()->position();
	VEC3I cell3d;

	for (unsigned int i = 0; i < md->numParticle(); i++){
		cell3d = getCellNumber(pos[i].x, pos[i].y, pos[i].z);
		cell_id[i] = getHash(cell3d);
		body_id[i] = i;
	}

	thrust::sort_by_key(cell_id, cell_id + md->numParticle(), body_id);
	memset(cell_start, 0xffffffff, sizeof(unsigned int) * ng);
	memset(cell_end, 0, sizeof(unsigned int)*ng);
	unsigned int begin = 0, end = 0, id = 0;
	bool ispass;
	while (end++ != md->numParticle()){
		ispass = true;
		id = cell_id[begin];
		if (id != cell_id[end]){
			end - begin > 1 ? ispass = false : reorderDataAndFindCellStart(id, begin++, end);
		}
		if (!ispass){
			reorderDataAndFindCellStart(id, begin, end);
			begin = end;
		}
	}
}