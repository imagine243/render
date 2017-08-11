#include "vector.h"

float vector::lenght() const
{
	return sqrtf(x * x + y * y + z * z);
}

vector vector::normalize() const {
	float factor = 0;
	float lenght = this->lenght();
	if (lenght > 0) factor = 1 / lenght;

	return vector(x*factor, y*factor, z*factor);
}

float vector::dot(const vector &v)const {
	return x*v.x + y*v.y + z*v.z;
}

vector vector::cross(const vector &v) const {
	float newx = y*v.z - z*v.y;
	float newy = z*v.x - x*v.z;
	float newz = x*v.y - y*v.x;
    return vector(newx, newy, newz);
}

vector vector::interpolate(const vector &v, float factor) const {
	return *this + (v - *this)*factor;
}
