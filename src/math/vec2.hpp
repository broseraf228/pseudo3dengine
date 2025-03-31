#pragma once

struct vec2 {
public:
	float x, y;

	vec2();
	vec2(float s);
	vec2(float x, float y);

	vec2 operator+(vec2 const&) const;
	vec2 operator-(vec2 const&) const;
	vec2 operator/(float) const;
	vec2 operator*(float) const;
	vec2 const& operator+=(vec2 const&);
	vec2 const& operator-=(vec2 const&);
	vec2 const& operator*=(float);
	vec2 const& operator/=(float);

	void ceil();
	float mod();
	vec2 norm();

	// scallar multiplication
	static float sclMul(vec2 const &, vec2 const &);
	
};

namespace v2d {
	vec2 const standart(1.0, 0);
}