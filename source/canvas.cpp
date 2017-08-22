#include "canvas.h"

#include <cfloat>
#include <iostream>

void Canvas::putPixel(int x, int y, float z, const color &c)
{
	int index = x + y * _width;
	float depth = _depthBuffer[index];

	if (depth < z)
	{
		return;
	}

	_depthBuffer[index] = z;
	_pixels[index] = c.uint32();
}

void Canvas::clear() {
	memset(_pixels, 0, sizeof(uint32_t)*_width * _height);
	std::fill(_depthBuffer, _depthBuffer + _bufferSize, FLT_MAX);
}

void Canvas::drawPoint(const vector &point, const color &color) 
{
	if (point.x >= 0 && point.y >= 0 && point.x < _width && point.y < _height) {
		putPixel(point.x, point.y, point.z, color);
	}
}

void Canvas::drawLine(const Vertex &v1, const Vertex &v2)
{
	int x1 = (int)v1.position.x;
	int y1 = (int)v1.position.y;
	int x2 = (int)v2.position.x;
	int y2 = (int)v2.position.y;

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dx) > abs(dy)) {
		int sign = x2 - x1 > 0 ? 1 : -1;
		float ratio = 0;
		if (dx != 0) {
			ratio = (float)dy / dx;
		}

		for (int x = x1; x != x2; x += sign)
		{
			int y = y1 + (x - x1) * ratio;
			color c = v1.c.interpolate(v2.c, (float)(x - x1) / (x2 - x1));
			drawPoint(vector(x, y), c);
		}
	}
	else
	{
		int sign = y2 - y1 > 0 ? 1:-1;
		float ratio = 0;
		if (dy != 0) {
			ratio = (float)dx / dy;
		}

		for (int y = 0; y != y2; y += sign)
		{
			int x = x1 + (y - y1)*ratio;
			color c = v1.c.interpolate(v2.c, (float)(y - y1) / (y2 - y1));
			drawPoint(vector(x, y), c);
		}
	}
}

void Canvas::drawScanLine(const Vertex &v1, const Vertex  &v2, int y, const texture *t)
{
	int x1 = v1.position.x;
	int x2 = v2.position.x;

	int sign = x2 > x1 ? 1 : -1;

	float factor = 0;
	int length = (x2 - x1) * sign + 1;
	for (int x = x1 ,i = 0; i < length; i++, x += sign)
	{
		if (x2 != x1) {
			factor = (float)(x - x1) / (x2 - x1);
		}

		auto v = v1.interpolate(v2, factor);
        if(t == NULL){
            drawPoint(vector(x,y,v.position.z), v.c);
        }else{
            auto c = t->sample(v.u, v.v);
            drawPoint(vector(x,y,v.position.z), c);
        }
	}

}

void Canvas::drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const texture *t)
{
	const Vertex *a = &v1;
	const Vertex *b = &v2;
	const Vertex *c = &v3;

	if (a->position.y > b->position.y) std::swap(a, b);
	if (b->position.y > c->position.y) std::swap(b, c);
	if (a->position.y > b->position.y) std::swap(a, b);

	Vertex middleAC = a->interpolate(*c, (float)(b->position.y - a->position.y) / (c->position.y - a->position.y));

	int startY = a->position.y;
	int endY = b->position.y;
	for (int y = startY; y <=  endY; y++)
	{
		float factor = 0;
		if (endY != startY) {
			factor = (float)(y - startY)/(endY - startY);
		}

		Vertex va = a->interpolate(*b, factor);
		Vertex vb = a->interpolate(middleAC, factor);
		drawScanLine(va, vb, y, t);
	}

	startY = b->position.y;
	endY = c->position.y;
	for (int y = startY; y <= endY; y++)
	{
		float factor = 0;
		if (endY != startY) {
			factor = (float)(y - startY) / (endY - startY);
		}

		Vertex va = b->interpolate(*c, factor);
		Vertex vb = middleAC.interpolate(*c, factor);
		drawScanLine(va, vb, y, t);
	}

}

void Canvas::drawMash(const Mesh &mesh)
{
	static const auto cameraPosition = vector(0, 0, -10);
	static const auto cameraTarget = vector(0, 0, 0);
	static const auto cameraUp = vector(0, 1, 0);

	static auto view = matrix::lookAtLH(cameraPosition, cameraTarget, cameraUp);
	static auto projection = matrix::perspectiveFovLH(radiansFromDegrees(45), _width / _height, 0.1, 1);

	auto rotation = matrix::rotation(mesh.rotation);
	auto translation = matrix::translation(mesh.position);
	auto scale = matrix::scale(mesh.scale);

	auto world = scale * rotation * translation;
	auto transform = world * view * projection;

	for (unsigned int i = 0; i < mesh.indices.size(); i += 3)
	{
		const Vertex &a = mesh.vertices[mesh.indices[i]];
		const Vertex &b = mesh.vertices[mesh.indices[i + 1]];
		const Vertex &c = mesh.vertices[mesh.indices[i + 2]];

		auto v1 = project(a, transform);
		auto v2 = project(b, transform);
		auto v3 = project(c, transform);

		drawTriangle(v1, v2, v3, mesh.t);
	}
}


Vertex Canvas::project(const Vertex &v, const matrix &transform) const
{
	vector p = transform.transform(v.position);
	p.x = p.x * _width + _width / 2;
	p.y = -p.y * _height + _height / 2;
    
    std::cout<< p.z << std::endl;
	return Vertex(p, v.normal, v.u, v.v, v.c);
}
