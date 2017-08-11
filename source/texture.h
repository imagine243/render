#ifndef _render_texture_
#define _render_texture_

#include "color.h"
class texture
{
private:
	uint32_t * _pixels;
	int _width;
	int _height;
public:
	texture(const char * path);
	virtual ~texture() {
		delete [] _pixels;
	};

	color sample(float u, float v) const;

};


#endif // !_render_texture_

