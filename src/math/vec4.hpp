#pragma once

struct vec4 {
public:
	float x, y, z, u;

	vec4();
	vec4(float s);
	vec4(float x, float y, float z, float u);

	vec4 operator+(vec4 const&) const;
	vec4 operator-(vec4 const&) const;
	vec4 operator/(float) const;
	vec4 operator*(float) const;
	vec4 const& operator+=(vec4 const&);
	vec4 const& operator-=(vec4 const&);
	vec4 const& operator*=(float);
	vec4 const& operator/=(float);

	vec4 operator-() const;

	void ceil();
	float mod() const;
	float nosMod() const;
	vec4 norm();

	// scallar multiplication
	static float sclMul(vec4 const &, vec4 const &);
	
};