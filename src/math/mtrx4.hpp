#pragma once

#include "vec4.hpp"

struct mtrx4 {
	vec4 e1;
	vec4 e2;
	vec4 e3;
	vec4 e4;

	mtrx4(const vec4& e = 0);
	// ����������� ������. ���� �1 - ������ ������, �2 - ������ � ��
	mtrx4(const vec4& e1 , const vec4& e2, const vec4& e3, const vec4& e4);

	vec4 operator*(vec4 const&);
	mtrx4 operator*(mtrx4 const&);

	void swap_by_diogonale();

	static mtrx4 mtrx_scale(vec4 const&);
	// angle in radians
	static mtrx4 mtrx_rotation(float);

	void ceil();
};