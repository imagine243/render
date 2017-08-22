#ifndef _render_mesh_
#define _render_mesh_

#include <vector>

#include "vector.h"
#include "vertex.h"
#include "texture.h"


class Mesh
{
public:
	
	vector position;
	vector rotation;
	vector scale;

	std::vector<Vertex> vertices;
	std::vector<int> indices;

	texture * t = NULL;

	Mesh() {
		position = vector(0, 0, 0);
		rotation = vector(0, 0, 0);
		scale = vector(1, 1, 1);
	};

	Mesh(const char *path, const char * texturePath);

	virtual ~Mesh() {
		delete t;
	};

};


#endif // !_render_mesh_

