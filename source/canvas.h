#ifndef _render_canvas_
#define _render_canvas_

#include <cstdint>

#include "color.h"
#include "vector.h"
#include "vertex.h"
#include "texture.h"
#include "Mesh.h"
#include "matrix.h"

class Canvas
{
private:
	
	uint32_t * _pixels;
	float *_depthBuffer;
	int _bufferSize;
	int _width;
	int _height;

	void putPixel(int x, int y, float z, const color &c);
public:
	Canvas(uint32_t * pixels, int width, int height) {
		_pixels = pixels;
		_width = width;
		_height = height;

		_bufferSize = width * height;
		_depthBuffer = new float[_bufferSize];
	};
	virtual ~Canvas(){
		delete[] _depthBuffer;
	};

	void clear();

	void drawPoint(const vector &point, const color &color);
	void drawLine(const Vertex &v1, const Vertex &v2);
	void drawScanLine(const Vertex &v1, const Vertex  &v2, int y, const texture *t);
	void drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const texture *t);
	void drawMash(const Mesh &mesh);

	Vertex project(const Vertex &v, const matrix &transform) const;
};


#endif // !_render_canvas_

