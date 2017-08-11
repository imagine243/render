#ifndef _render_canvas_
#define _render_canvas_

#include <cstdint>

class Canvas
{
private:
	
	uint32_t * _pixels;
	float *_depthBuffer;
	int _bufferSize;
	int _width;
	int _height;
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


};


#endif // !_render_canvas_

