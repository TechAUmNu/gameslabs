#include <iostream>

using namespace std;

class vec3 {
public:

	float x;
	float y;
	float z;

	// populated constructor
	vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	// default constructor
	vec3() {
	}


	// Operators

	vec3 operator+(const vec3& v1) {
		return(vec3(
			x + v1.x,
			y + v1.y,
			z + v1.z));
	};

	vec3 operator+(float scalar) {
		return(vec3(
			x + scalar,
			y + scalar,
			z + scalar));
	};

	vec3 operator-(const vec3& v1) {
		return(vec3(
			x - v1.x,
			y - v1.y,
			z - v1.z));
	};

	vec3 operator-(float scalar) {
		return(vec3(
			x - scalar,
			y - scalar,
			z - scalar));
	};

	vec3 operator*(const vec3& v1) {
		return(vec3(
			x * v1.x,
			y * v1.y,
			z * v1.z));
	};

	vec3 operator*(float scalar) {
		return(vec3(
			x * scalar,
			y * scalar,
			z * scalar));
	};

	vec3 operator/(const vec3& v1) {
		return(vec3(
			x / v1.x,
			y / v1.y,
			z / v1.z));
	};

	vec3 operator/(float scalar) {
		return(vec3(
			x / scalar,
			y / scalar,
			z / scalar));
	};

	




	vec3 operator+=(const vec3& v1) {
		x += v1.x;
		y += v1.y;
		z += v1.z;
		return *this;
	};

	vec3 operator+=(float scalar) {
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	};

	vec3 operator-=(const vec3& v1) {
		x -= v1.x;
		y -= v1.y;
		z -= v1.z;
		return *this;
	};

	vec3 operator-=(float scalar) {
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	};

	vec3 operator*=(const vec3& v1) {
		x *= v1.x;
		y *= v1.y;
		z *= v1.z;
		return *this;
	};

	vec3 operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	};

	vec3 operator/=(const vec3& v1) {
		x /= v1.x;
		y /= v1.y;
		z /= v1.z;
		return *this;
	};

	vec3 operator/=(float scalar) {
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	};



	bool operator==(const vec3& v1) {
		return (v1.x == x) && (v1.y == y) && (v1.z == z);
	}

	
	bool operator!=(const vec3& v1) {
		return (v1.x != x) || (v1.y != y) || (v1.z != z);
	}

	



	vec3 cross(const vec3& rhs) {
		return vec3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	float dot(const vec3& rhs) {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}	

	static vec3 cross(const vec3& v1, const vec3& v2) {
		return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	static float dot(const vec3& v1, const vec3& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	vec3 triplevec(vec3& v1, vec3& v2) {
		return cross(v1.cross(v2));
	}

	static vec3 triplevec(vec3& v1, vec3& v2, vec3& v3) {
		return vec3::cross(v3, v1.cross(v2));
	}
	
	float triplescal(vec3& v1, vec3& v2) {
		return dot(v1.cross(v2));
	}
	
	static float triplescal(vec3& v1, vec3& v2, vec3& v3) {
		return vec3::dot(v3, v1.cross(v2));
	}

};

// new code
ostream &operator <<(ostream &stream, vec3 v) {
	cout << "(" << v.x << "," << v.y << "," << v.z << ")";
	return stream;
};

int main() {
	vec3 v1(3, 6, 6);
	vec3 v2(2, -2, 2);
	vec3 v3 = v1 + v2;
	cout << "v3 =" << v3 << endl;

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}