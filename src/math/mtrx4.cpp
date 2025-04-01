#include "mtrx4.hpp"
#include <cmath>
#include <algorithm>

mtrx4::mtrx4(const vec4& e) : e1{ e }, e2{ e }, e3{ e }, e4{ e } {};
mtrx4::mtrx4(const vec4& e1, const vec4& e2, const vec4& e3, const vec4& e4) : e1{ e1 }, e2{ e2 }, e3{ e3 }, e4{ e4 } {}

vec4 mtrx4::operator*(vec4 const& other) const {
	return vec4
	(
		vec4::sclMul(other, e1),
		vec4::sclMul(other, e2),
		vec4::sclMul(other, e3),
		vec4::sclMul(other, e4)
	);
}

mtrx4 mtrx4::operator*(mtrx4 const& other) const {

	mtrx4 other_ = other;
	other_.swap_by_diogonale();

	return mtrx4
	(
		*this * other_.e1,
		*this * other_.e2,
		*this * other_.e3,
		*this * other_.e4
	);
}

void mtrx4::swap_by_diogonale(){
	std::swap(e1.y, e2.x);
	std::swap(e1.z, e3.x);
	std::swap(e1.u, e4.x);
	std::swap(e2.z, e3.y);
	std::swap(e2.u, e4.y);
	std::swap(e3.u, e4.z);
}