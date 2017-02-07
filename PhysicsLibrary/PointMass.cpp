#include "PointMass.h"

	PointMass::PointMass(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass) {
		position = pos;
		velocity = vel;
		this->force = force;
		friction = frict;
		this->gravity = gravity;		
		this->mass = mass;
	}

	// Called every frame
	void PointMass::update(float deltaTime) {
		acceleration = (force + friction) / mass;
		velocity += acceleration * deltaTime;
		if (gravity) {
			velocity.y += -9.81f;
		}
		
		position = velocity * deltaTime;

	}


