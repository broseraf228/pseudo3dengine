#pragma once

#include "vec2.hpp"

struct mtrx2 {
	vec2 e1;
	vec2 e2;

	mtrx2();
	// not work. Dotn't use this
	mtrx2(const vec2& e);
	mtrx2(const vec2& e1 , const vec2& e2);

	mtrx2 operator+(mtrx2 const&);
	mtrx2 operator-(mtrx2 const&);
	mtrx2 operator*(float);
	mtrx2 operator/(float);
	void operator+=(mtrx2 const&);
	void operator-=(mtrx2 const&);
	void operator*=(float);
	void operator/=(float);

	vec2 operator*(vec2 const&);
	mtrx2 operator*(mtrx2 const&);

	static mtrx2 mtrx_scale(vec2 const&);
	// angle in radians
	static mtrx2 mtrx_rotation(float);

	void ceil();
};