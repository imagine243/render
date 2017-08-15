#pragma once

#ifndef _render_matrix_
#define	_render_matrix_

#include "rmath.h"
#include "vector.h"

class matrix
{
public:
	float p[16];
	matrix()
	{
		for (int i = 0; i < 16; i++)
		{
			p[i] = 0;
		}
	};

	matrix(float values[]) {
		for (int i = 0; i < 16; i++)
		{
			p[i] = values[i];
		}
	};

	bool operator==(const matrix &m) const {
		bool equal = true;
		for (int i = 0; i < 16; i++)
		{
			equal = equal && floatEqual(p[i], m.p[i]);
		}
		return equal;
	};

	matrix operator*(const matrix &m) const {
		float values[16];
		for (int index = 0; index < 16; index++) {
			int i = index / 4;
			int j = index % 4;
			values[index] = p[i * 4] * m.p[j] + p[i * 4 + 1] * m.p[1 * 4 + j] + p[i * 4 + 2] * m.p[2 * 4 + j] + p[i * 4 + 3] * m.p[3 * 4 + j];
		}
		return matrix(values);
	}

	static matrix identity() {
		float values[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		return matrix(values);
	};

	static matrix lookAtLH(const vector &eye, const vector &target, const vector &up)
	{
		vector axisZ = (target - eye).normalize();
		vector axisX = up.cross(axisZ).normalize();
		vector axisY = axisZ.cross(axisX).normalize();

		float eyeX = -axisX.dot(eye);
		float eyeY = -axisY.dot(eye);
		float eyeZ = -axisZ.dot(eye);

		float values[16] = {
			axisX.x, axisY.x, axisZ.x, 0,
			axisX.y, axisY.y, axisZ.y, 0,
			axisX.z, axisY.z, axisZ.z, 0,
			eyeX,    eyeY,    eyeZ,    0,
		};
		return matrix(values);
	};

	static matrix perspectiveFovLH(float fieldOfView, float aspect, float znear, float zfar) {
		float height = 1 / tan(fieldOfView / 2);
		float width = height / aspect;
		float values[16] = {
			width,  0,      0,                                  0,
			0,      height, 0,                                  0,
			0,      0,      zfar / (zfar - znear),              1,
			0,      0,      (znear * zfar) / (znear - zfar),    0,
		};
		return matrix(values);
	};

	static matrix rotationX(float angle) {
		float s = sinf(angle);
		float c = cosf(angle);

		float values[16] = {
			1, 0, 0, 0,
			0, c, s, 0,
			0, -s,c, 0,
			0, 0, 0, 1,
		};
		return matrix(values);
	};

	static matrix rotationY(float angle) {
		float s = sinf(angle);
		float c = cosf(angle);

		float values[16] = {
			c, 0, -s, 0,
			0, 1, 0, 0,
			s, 0, c, 0,
			0, 0, 0, 1,
		};
		return matrix(values);
	};
	static matrix rotationZ(float angle) {
		float s = sinf(angle);
		float c = cosf(angle);

		float values[16] = {
			c, s, 0, 0,
			-s,c, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		return matrix(values);
	};

	static matrix rotation(const vector &r) {
		matrix x = matrix::rotation(r.x);
		matrix y = matrix::rotation(r.y);
		matrix z = matrix::rotation(r.z);
		
		return z * x * y;
	};

	static matrix translation(const vector &t) {
		float values[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			t.x, t.y, t.z, 1,
		};
		return matrix(values);
	};

	static matrix scale(const vector &s) {
		float values[16] = {
			s.x, 0, 0, 0,
			0, s.y, 0, 0,
			0, 0, s.z, 0,
			0, 0, 0, 1,
		};
		return matrix(values);
	}

	vector transform(const vector &v) const {
		float x = v.x * p[0 * 4 + 0] + v.y * p[1 * 4 + 0] + v.z * p[2 * 4 + 0] + p[3 * 4 + 0];
		float y = v.x * p[0 * 4 + 1] + v.y * p[1 * 4 + 1] + v.z * p[2 * 4 + 1] + p[3 * 4 + 1];
		float z = v.x * p[0 * 4 + 2] + v.y * p[1 * 4 + 2] + v.z * p[2 * 4 + 2] + p[3 * 4 + 2];
		float w = v.x * p[0 * 4 + 3] + v.y * p[1 * 4 + 3] + v.z * p[2 * 4 + 3] + p[3 * 4 + 3];
		return vector(x / w, y / w, z / w);
	}

	virtual ~matrix()
    {
        
    };


};


#endif // !_render_matrix_

