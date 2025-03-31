#include "mtrx2.hpp"
#include <cmath>

mtrx2::mtrx2() : e1(vec2()), e2(vec2()) {}
mtrx2::mtrx2(const vec2& e) {}
mtrx2::mtrx2(const vec2& e1, const vec2& e2) : e1(e1), e2(e2) {}

mtrx2 mtrx2::operator+(mtrx2 const& other) {
	return mtrx2
	(
		this->e1 + other.e1,
		this->e2 + other.e2
	);
}
mtrx2 mtrx2::operator-(mtrx2 const& other) {
	return mtrx2
	(
		this->e1 - other.e1,
		this->e2 - other.e2
	);
}
mtrx2 mtrx2::operator*(float s) {
	return mtrx2
	(
		this->e1 * s,
		this->e2 * s
	);
}
mtrx2 mtrx2::operator/(float s) {
	return mtrx2
	(
		this->e1 / s,
		this->e2 / s
	);
}

void mtrx2::operator+=(mtrx2 const& other) {
	this->e1 += other.e1;
	this->e2 += other.e2;
}
void mtrx2::operator-=(mtrx2 const& other) {
	this->e1 -= other.e1;
	this->e2 -= other.e2;
}
void mtrx2::operator*=(float s) {
	this->e1 *= s;
	this->e2 *= s;
}
void mtrx2::operator/=(float s) {
	this->e1 /= s;
	this->e2 /= s;
}

vec2 mtrx2::operator*(vec2 const& other) {
	return vec2
	(
		e1.x * other.x + e2.x * other.y,
		e1.y * other.x + e2.y * other.y
	);
}

mtrx2 mtrx2::operator*(mtrx2 const& other) {
	return mtrx2
	(
		vec2
		(
			e1.x * other.e1.x + e2.x * other.e1.y,
			e1.y * other.e1.x + e2.y * other.e1.y
		),
		vec2
		(
			e1.x * other.e2.x + e2.x * other.e2.y,
			e1.y * other.e2.x + e2.y * other.e2.y
		)
	);
}

mtrx2 mtrx2::mtrx_rotation(float angle) {
	return mtrx2
	(
		vec2(cos(angle),sin(angle)),
		vec2(-sin(angle), cos(angle))
	);
}

void mtrx2::ceil() {
	e1.ceil();
	e2.ceil();
}