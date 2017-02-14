#include <iostream>
#include "vec3.h"
#include <random>



	// populated constructor
	vec3::vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// default constructor
	vec3::vec3() {
	}

	// deconstructor
	vec3::~vec3() {
	}


	// Operators

	vec3 vec3::operator+(const vec3& v1) {
		return(vec3(
			x + v1.x,
			y + v1.y,
			z + v1.z));
	};

	vec3 vec3::operator+(float scalar) {
		return(vec3(
			x + scalar,
			y + scalar,
			z + scalar));
	};

	vec3 vec3::operator-(const vec3& v1) {
		return(vec3(
			x - v1.x,
			y - v1.y,
			z - v1.z));
	};

	vec3 vec3::operator-(float scalar) {
		return(vec3(
			x - scalar,
			y - scalar,
			z - scalar));
	};

	void vec3::subtractFast(vec3 *temp, vec3 *lhs, vec3 *rhs) {
		temp->x = lhs->x - rhs->x;
		temp->y = lhs->y - rhs->y;
		temp->z = lhs->z - rhs->z;
	}

	vec3 vec3::operator*(const vec3& v1) {
		return(vec3(
			x * v1.x,
			y * v1.y,
			z * v1.z));
	};

	vec3 vec3::operator*(float scalar) {
		return(vec3(
			x * scalar,
			y * scalar,
			z * scalar));
	};

	vec3 vec3::operator/(const vec3& v1) {
		return(vec3(
			x / v1.x,
			y / v1.y,
			z / v1.z));
	};

	vec3 vec3::operator/(float scalar) {
		return(vec3(
			x / scalar,
			y / scalar,
			z / scalar));
	};



	vec3 vec3::operator+=(const vec3& v1) {
		x += v1.x;
		y += v1.y;
		z += v1.z;
		return *this;
	};

	vec3 vec3::operator+=(float scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	};

	vec3 vec3::operator-=(const vec3& v1) {
		x -= v1.x;
		y -= v1.y;
		z -= v1.z;
		return *this;
	};

	vec3 vec3::operator-=(float scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	};

	vec3 vec3::operator*=(const vec3& v1) {
		x *= v1.x;
		y *= v1.y;
		z *= v1.z;
		return *this;
	};

	vec3 vec3::operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	};

	vec3 vec3::operator/=(const vec3& v1) {
		x /= v1.x;
		y /= v1.y;
		z /= v1.z;
		return *this;
	};

	vec3 vec3::operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	};



	bool vec3::operator==(const vec3& v1) {
		return (v1.x == x) && (v1.y == y) && (v1.z == z);
	};

	
	bool vec3::operator!=(const vec3& v1) {
		return (v1.x != x) || (v1.y != y) || (v1.z != z);
	};

	



	vec3 vec3::cross(const vec3& rhs) {
		return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	};

	float vec3::dot(const vec3& rhs) {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	};

	vec3 vec3::cross(const vec3& v1, const vec3& v2) {
		return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	};

	float vec3::dot(const vec3& v1, const vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	};

	vec3 vec3::triplevec(vec3& v1, vec3& v2) {
		return cross(v1.cross(v2));
	};

	vec3 vec3::triplevec(vec3& v1, vec3& v2, vec3& v3) {
		return vec3::cross(v3, v1.cross(v2));
	};
	
	float vec3::triplescal(vec3& v1, vec3& v2) {
		return dot(v1.cross(v2));
	};
	
	float vec3::triplescal(vec3& v1, vec3& v2, vec3& v3) {
		return vec3::dot(v3, v1.cross(v2));
	};

	vec3 vec3::up() {
		return vec3(0, 1, 0);
	};

	vec3 vec3::down() {
		return vec3(0, -1, 0);
	};

	vec3 vec3::forward() {
		return vec3(0, 0, 1);
	};

	vec3 vec3::back() {
		return vec3(0, 0, -1);
	};

	vec3 vec3::left() {
		return vec3(-1, 0, 0);
	};

	vec3 vec3::right() {
		return vec3(1, 0, 0);
	};

	vec3 vec3::one() {
		return vec3(1, 1, 1);
	};

	vec3 vec3::zero() {
		return vec3(0, 0, 0);
	};

	float vec3::magnitude()
	{		
		return sqrtf(pow(x,2) + pow(y, 2) + pow(z, 2));
	};

	vec3 vec3::absolute()
	{
		return vec3(abs(x), abs(y), abs(z));
	};

	vec3 vec3::random(std::pair<vec3, vec3> range) {
		std::default_random_engine engine;
		engine.seed(std::random_device{}());
		std::uniform_real_distribution<> xGenerator(range.first.x, range.second.x);
		std::uniform_real_distribution<> yGenerator(range.first.y, range.second.y);
		std::uniform_real_distribution<> zGenerator(range.first.z, range.second.z);
		return vec3(xGenerator(engine), yGenerator(engine), zGenerator(engine));
	};

	vec3 vec3::normalize(float multiplier){
		
		float length = magnitude();
		if (length == 0) return *this;
		x = (x / length) * multiplier;
		y = (y / length) * multiplier;
		z = (z / length) * multiplier;		
		return *this;
	};
	
	vec3 * vec3::set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;

		return this;
	};



