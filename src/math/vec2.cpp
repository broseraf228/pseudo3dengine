#include "vec2.hpp"
#include <cmath>

vec2::vec2() : vec2(0) {}
vec2::vec2(float s) : vec2(0, 0) {}
vec2::vec2(float x, float y) : x{x}, y{y} {}

vec2 vec2::operator+(const vec2& other) const
{
	return vec2(this->x + other.x, this->y + other.y);
}
vec2 vec2::operator-(const vec2& other) const
{
	return vec2(this->x - other.x, this->y - other.y);
}
vec2 vec2::operator/(float other) const
{
	return vec2(this->x / other, this->y / other);
}
vec2 vec2::operator*(float other) const
{
	return vec2(this->x * other, this->y * other);
}
vec2 const& vec2::operator+=(const vec2& other)
{
	this->x += other.x, this->y += other.y;
	return *this;
}
vec2 const& vec2::operator-=(const vec2& other)
{
	this->x -= other.x, this->y -= other.y;
	return *this;
}
vec2 const& vec2::operator/=(float other)
{
	this->x /= other, this->y /= other;
	return *this;
}
vec2 const& vec2::operator*=(float other)
{
	this->x *= other, this->y *= other;
	return *this;
}

float vec2::mod() {
	return  sqrtf(x * x + y * y);
}
vec2 vec2::norm() {
	float l = mod();
	return  vec2(x / l, y / l);
}
float vec2::sclMul(const vec2& a, const vec2& b) {
	return (a.x * b.x + a.y * b.y);
}
void vec2::ceil()
{
	x = int(x * 1000) * 0.001;
	y = int(y * 1000) * 0.001;
}