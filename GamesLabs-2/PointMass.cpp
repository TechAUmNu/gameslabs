
#include "../MathsLibrary/vec3.h"
#include "PointMass.h";

class PointMass {
public:

	
	vec3 position, velocity, force, friction;

	// Gravity Toggle
	bool gravity = false;

	float mass = 1;

	PointMass(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass) {
		position = pos;
		velocity = vel;
		this->force = force;
		friction = frict;
		this->gravity = gravity;		
		this->mass = mass;
	}

	// Called every frame
	void update(float deltaTime) {		
		
		velocity += (force + friction) / mass;
		if (gravity) {
			velocity.y += 9.81;
		}
		
		position = velocity * deltaTime;

	}

	
};
