#pragma once
#include <utility>


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

	static void subtractFast(vec3* temp, vec3* lhs, vec3* rhs);

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

	static vec3 up();

	static vec3 down();

	static vec3 forward();

	static vec3 back();

	static vec3 left();

	static vec3 right();

	static vec3 one();

	static vec3 zero();

	float magnitude();

	vec3 absolute();

	static vec3 random(std::pair<vec3, vec3> velocityRange);

	vec3 normalize(float multiplier);

};