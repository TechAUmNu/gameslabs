#include "RigidBody.h"
#include <iostream>
using namespace std;

	RigidBody::RigidBody(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass) {
		this->position = position;
		this->velocity = velocity;
		this->force = force;
		this->material = material;
		this->drag = drag;
		this->useGravity = gravity;		
		this->mass = mass;
	}

	// Called every frame
	void RigidBody::update(float deltaTime) {
		
		if (!isKinematic) {
			acceleration = (force) / mass;
			velocity += acceleration * deltaTime;
			if (useGravity) {
				velocity.y += -9.81f * deltaTime;
			}

			position += velocity * deltaTime;			
		}
	}


