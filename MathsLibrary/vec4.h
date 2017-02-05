#pragma once

class vec4 {

public:

	float x, y, z, w;

	// populated constructor
	vec4(float x, float y, float z, float w);

	// default constructor
	vec4();
	~vec4();

	// Operators

	vec4 operator+(const vec4& v1);

	vec4 operator+(float scalar);

	vec4 operator-(const vec4& v1);

	vec4 operator-(float scalar);

	vec4 operator*(const vec4& v1);

	vec4 operator*(float scalar);

	vec4 operator/(const vec4& v1);

	vec4 operator/(float scalar);


	vec4 operator+=(const vec4& v1);

	vec4 operator+=(float scalar);

	vec4 operator-=(const vec4& v1);

	vec4 operator-=(float scalar);

	vec4 operator*=(const vec4& v1);

	vec4 operator*=(float scalar);

	vec4 operator/=(const vec4& v1);

	vec4 operator/=(float scalar);


	bool operator==(const vec4& v1);

	bool operator!=(const vec4& v1);	

};