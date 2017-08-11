#ifndef _render_color_
#define _render_color_

#include <cstdint>
#include <cstdlib>


class color {
public:
	float r;
	float g;
	float b;
	float a;

	color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	color(uint32_t rgba);

	static color randomColor() {
		float r = (rand() % 255) / 255.0f;
		float g = (rand() % 255) / 255.0f;
		float b = (rand() % 255) / 255.0f;
		return color(r, g, b, 1);
	}

	uint32_t uint32() const;

	color operator+(const color &c) const {
		return color(this->r + c.r, this->g + c.g, this->b + c.b, this->a + c.a);
	};

	color operator-(const color &c) const {
		return color(this->r - c.r, this->g - c.g, this->b - c.b, this->a - c.a);
	};

	color operator*(float factor) const {
		return color(r * factor, g * factor, b * factor, a * factor);
	};

	color interpolate(const color &c, float factor) const {
		return *this + (c - *this)*factor;
	};
};


#endif // !_render_color_

