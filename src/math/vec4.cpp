#include "vec4.hpp"
#include <cmath>

vec4::vec4() : vec4(0) {}
vec4::vec4(float s) : vec4(s, s, s, s) {}
vec4::vec4(float x, float y, float z, float u) : x{ x }, y{ y }, z{ z }, u{ u } {}

vec4 vec4::operator+(const vec4& other) const
{
	return vec4(this->x + other.x, this->y + other.y, this->z + other.z, this->u + other.u);
}
vec4 vec4::operator-(const vec4& other) const
{
	return vec4(this->x - other.x, this->y - other.y, this->z - other.z, this->u - other.u);
}
vec4 vec4::operator/(float other) const
{
	return vec4(this->x / other, this->y / other, this->z / other, this->u / other);
}
vec4 vec4::operator*(float other) const
{
	return vec4(this->x * other, this->y * other, this->z * other, this->u * other);
}
vec4 const& vec4::operator+=(const vec4& other)
{
	this->x += other.x, this->y += other.y, this->z += other.z, this->u += other.u;
	return *this;
}
vec4 const& vec4::operator-=(const vec4& other)
{
	this->x -= other.x, this->y -= other.y, this->z -= other.z, this->u -= other.u;
	return *this;
}
vec4 const& vec4::operator/=(float other)
{
	this->x /= other, this->y /= other, this->z /= other, this->u /= other;
	return *this;
}
vec4 const& vec4::operator*=(float other)
{
	this->x *= other, this->y *= other, this->z *= other, this->u *= other;
	return *this;
}

float vec4::mod() const {
	return  sqrtf(x * x + y * y + z * z + u * u);
}
vec4 vec4::norm() {
	float l = mod();
	return  vec4(x / l, y / l, z / l , u / l);
}
float vec4::sclMul(const vec4& a, const vec4& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.u * b.u);
}

void vec4::ceil()
{
	x = int(x * 1000) * 0.001;
	y = int(y * 1000) * 0.001;
	z = int(z * 1000) * 0.001;
	u = int(u * 1000) * 0.001;
}