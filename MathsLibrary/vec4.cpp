#include <iostream>
#include "vec4.h"
#include "vec3.h"
#include "../lib/glm/glm/glm.hpp"
#include <random>
using namespace std;

// populated constructor
vec4::vec4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

// default constructor
vec4::vec4() {
	}

	// deconstructor
vec4::~vec4() {
	}


	// Operators

	vec4 vec4::operator+(const vec4& v1) {
		return(vec4(
			x + v1.x,
			y + v1.y,
			z + v1.z,
			w + v1.w));
	};

	vec4 vec4::operator+(float scalar) {
		return(vec4(
			x + scalar,
			y + scalar,
			z + scalar,
			w + scalar));
	};

	vec4 vec4::operator-(const vec4& v1) {
		return(vec4(
			x - v1.x,
			y - v1.y,
			z - v1.z,
			w - v1.w));
	};

	vec4 vec4::operator-(float scalar) {
		return(vec4(
			x - scalar,
			y - scalar,
			z - scalar,
			w - scalar));
	};

	vec4 vec4::operator*(const vec4& v1) {
		return(vec4(
			x * v1.x,
			y * v1.y,
			z * v1.z,
			w * v1.w));
	};

	vec4 vec4::operator*(float scalar) {
		return(vec4(
			x * scalar,
			y * scalar,
			z * scalar,
			w * scalar));
	};

	vec4 vec4::operator/(const vec4& v1) {
		return(vec4(
			x / v1.x,
			y / v1.y,
			z / v1.z,
			w / v1.w));
	};

	vec4 vec4::operator/(float scalar) {
		return(vec4(
			x / scalar,
			y / scalar,
			z / scalar,
			w / scalar));
	};






	vec4 vec4::operator+=(const vec4& v1) {
		x += v1.x;
		y += v1.y;
		z += v1.z;
		w += v1.w;
		return *this;
	};

	vec4 vec4::operator+=(float scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	};

	vec4 vec4::operator-=(const vec4& v1) {
		x -= v1.x;
		y -= v1.y;
		z -= v1.z;
		w -= v1.w;
		return *this;
	};

	vec4 vec4::operator-=(float scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	};

	vec4 vec4::operator*=(const vec4& v1) {
		x *= v1.x;
		y *= v1.y;
		z *= v1.z;
		w *= v1.w;
		return *this;
	};

	vec4 vec4::operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	};

	vec4 vec4::operator/=(const vec4& v1) {
		x /= v1.x;
		y /= v1.y;
		z /= v1.z;
		w /= v1.w;
		return *this;
	};

	vec4 vec4::operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	};



	bool vec4::operator==(const vec4& v1) {
		return (v1.x == x) && (v1.y == y) && (v1.z == z) && (v1.w == w);
	}


	bool vec4::operator!=(const vec4& v1) {
		return (v1.x != x) || (v1.y != y) || (v1.z != z) || (v1.w != z);
	}

	glm::vec4 vec4::toGlmVec4(const vec4& v1) {
		return glm::vec4(v1.x, v1.y, v1.z, v1.w);
	}

	glm::vec4 vec4::toGlmVec4() {
		return glm::vec4(x, y, z, w);
	}

	vec4 vec4::random(std::pair<vec3, vec3> range) {
		std::default_random_engine engine;
		engine.seed(std::random_device{}());
		std::uniform_real_distribution<> xGenerator(range.first.x, range.second.x);
		std::uniform_real_distribution<> yGenerator(range.first.y, range.second.y);
		std::uniform_real_distribution<> zGenerator(range.first.z, range.second.z);		
		return vec4(xGenerator(engine), yGenerator(engine), zGenerator(engine), 1.0f);
	};
