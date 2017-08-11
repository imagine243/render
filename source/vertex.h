#ifndef _render_vertex_
#define _render_vertex_

#include "vector.h"
#include "color.h"

class Vertex
{
public:
	vector position;
	vector normal;
	float u;
	float v;
	color c;

	Vertex(const vector &position, const vector	normal, float u, float v, const color &c = color())
	{
		this->position = position;
		this->normal = normal;
		this->u = u;
		this->v = v;
		this->c = c;
	};

	Vertex interpolate(const Vertex &vertex, float factor) const {
		vector p = position.interpolate(vertex.position, factor);
		vector n = normal.interpolate(vertex.normal, factor);
		float tu = u + (vertex.u - u) * factor;
		float tv = v + (vertex.v - v) * factor;
		color tc = c.interpolate(vertex.c, factor);

		return Vertex(p, n, tu, tv, tc);
	};

};

#endif // !_render_vertex_
