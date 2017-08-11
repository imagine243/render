#ifndef _render_image_
#define _render_image_

#include <fstream>
#include <string>
#include <sstream>

#include "color.h"
#include "rutil.h"


class Image
{
public:
	uint32_t * pixels;
	int width;
	int height;
	Image(const char * path);
	 virtual ~Image();


};

Image::Image(const char * path)
{
	std::ifstream imageFile(path);
	std::string line;

	// file description and version
	std::getline(imageFile, line);
	std::getline(imageFile, line);

	std::getline(imageFile, line);
	width = atoi(line.c_str);
	
	std::getline(imageFile, line);
	height = atoi(line.c_str);

	pixels = new uint32_t[width * height];
	const char delimiter = ' ';
	for (int i = 0; i < height; i++)
	{
		std::getline(imageFile, line);
		auto row = split(line, delimiter);
		for (int j = 0; j < width; j++)
		{
			std::stringstream s(row[j]);
			unsigned int pixel;
			s >> pixel;
			pixels[i * width + j] = pixel;
		}
	}
}

Image::~Image()
{
	delete[] pixels;
}

#endif // !_render_image_
