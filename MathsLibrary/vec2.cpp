#include <iostream>

using namespace std;

class vec2 {
public:
	// constructor with 2 parameters
	vec2(float f1, float f2) {
		x = f1;
		y = f2;
	}

	// constructor with 0 parameters
	vec2() {
	}

	// data
	float x;
	float y;

	vec2 operator+(const vec2& v1) {
		vec2 result;
		result.x = this->x + v1.x;
		result.y = this->y + v1.y;
		return result;
	};
};

// new code
ostream &operator <<(ostream &stream, vec2 v) {
	cout << "(" << v.x << "," << v.y << ")";
	return stream;
};

/*

int main() {
	vec2 v1(3, 6);
	vec2 v2(2, -2);
	vec2 v3 = v1 + v2;
	cout << "v3 =" << v3 << endl;

	cout << "\nPress any key to continue...\n";
	cin.ignore(); cin.get(); // delay closing console to read debugging errors.

	return 0;
}
*/