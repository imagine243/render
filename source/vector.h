#pragma once

#ifndef _render_vector_
#define _render_vector_

#include "rmath.h"

class vector
{
public:
	float x;
	float y;
	float z;
	vector(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	};

	float lenght() const;
	vector normalize() const;
	float dot(const vector &v)const;
	vector cross(const vector &v) const;
	vector interpolate(const vector &v, float factor) const;

	vector operator+(const vector &v) const {
		return vector(x + v.x, y + v.y, z + v.z);
	};

	vector operator-(const vector &v) const {
		return vector(x - v.x, y - v.y, z - v.z);
	};

	vector operator*(float factor)const {
		return vector(x* factor, y * factor, z* factor);
	};

	bool operator==(const vector &v)const {
		return floatEqual(v.x, x) && floatEqual(v.y, y) && floatEqual(v.z, z);
	};

private:

};


#endif // !_render_vector_

