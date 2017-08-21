#include "color.h"

color::color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

color::color(uint32_t rgba) {
	r = ((rgba & 0xff000000) >> 24) / 255.0f;
	g = ((rgba & 0x00ff0000) >> 24) / 255.0f;
	b = ((rgba & 0x0000ff00) >> 24) / 255.0f;
	a = ((rgba & 0x000000ff) >> 24) / 255.0f;
}

uint32_t color::uint32() const
{
	uint32_t R = (uint32_t)(r * 255.0f);
	uint32_t G = (uint32_t)(g * 255.0f);
	uint32_t B = (uint32_t)(b * 255.0f);
	uint32_t A = (uint32_t)(a * 255.0f);

//#ifdef __APPLE__
//	uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
//#elif _WIN32
//	uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
//#else
//	uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
//#endif
    
    uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
    
	return value;

}
