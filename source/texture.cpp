#include "texture.h"
#include "image.h"

texture::texture(const char * path)
{
	Image image = Image(path);
	int w = image.width;
	int h = image.height;
	uint32_t *pixels = new uint32_t[w * h];
	memcpy(pixels, image.pixels, sizeof(uint32_t) * w * h);
	_pixels = pixels;
	_width = w;
	_height = h;
}

color texture::sample(float u, float v) const {
	if (_pixels != NULL) {
		int tu = abs((int)(u * (_width - 1)));
		int tv = abs((int)(v * (_height - 1)));

		int index = tu + tv * _width;
		color c = color(_pixels[index]);
		return c;
	}
	else
	{
		return color();
	}
}
