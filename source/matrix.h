#pragma once

#ifndef _render_matrix_
#define	_render_matrix_

#include "rmath.h"

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

	static matrix identity() {
		float values[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
		};
		return matrix(values);
	};

	//static matrix lookAtLH()

	~matrix();

private:

};

matrix::matrix()
{
}

matrix::~matrix()
{
}


#endif // !_render_matrix_

