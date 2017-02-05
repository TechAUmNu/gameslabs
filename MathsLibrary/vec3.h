#pragma once

class vec3 {

public:

	float x, y, z;

	// populated constructor
	vec3(float x, float y, float z);

	// default constructor
	vec3();
	~vec3();

	// Operators

	vec3 operator+(const vec3& v1);

	vec3 operator+(float scalar);

	vec3 operator-(const vec3& v1);

	vec3 operator-(float scalar);

	vec3 operator*(const vec3& v1);

	vec3 operator*(float scalar);

	vec3 operator/(const vec3& v1);

	vec3 operator/(float scalar);


	vec3 operator+=(const vec3& v1);

	vec3 operator+=(float scalar);

	vec3 operator-=(const vec3& v1);

	vec3 operator-=(float scalar);

	vec3 operator*=(const vec3& v1);

	vec3 operator*=(float scalar);

	vec3 operator/=(const vec3& v1);

	vec3 operator/=(float scalar);


	bool operator==(const vec3& v1);

	bool operator!=(const vec3& v1);	

	vec3 cross(const vec3& rhs);

	float dot(const vec3& rhs);
	static vec3 cross(const vec3& v1, const vec3& v2);

	static float dot(const vec3& v1, const vec3& v2);

	vec3 triplevec(vec3& v1, vec3& v2);

	static vec3 triplevec(vec3& v1, vec3& v2, vec3& v3);

	float triplescal(vec3& v1, vec3& v2);

	static float triplescal(vec3& v1, vec3& v2, vec3& v3);

};