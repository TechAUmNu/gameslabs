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
		this->mass = 1;
	}

	// Called every frame
	void RigidBody::update(float deltaTime) {
		
		if (!isKinematic) {
			vec3 forceGrav;
			forceGrav = vec3::zero();
			forceGrav.y = -9.81f * mass;

			if (velocity.y > 0) {

				dragy.y = (velocity.y * velocity.y * -drag);
			}
			else {
				dragy.y = (velocity.y * velocity.y * drag);
			}

			if (velocity.x > 0) {

				dragy.x = (velocity.x * velocity.x * -drag);
			}
			else {
				dragy.x = (velocity.x * velocity.x * drag);
			}

			if (velocity.z > 0) {

				dragy.z = (velocity.z * velocity.z * -drag);
			}
			else {
				dragy.z = (velocity.z * velocity.z * drag);
			}
			
			//vec3 dragForce = ((velocity*velocity) * drag * 1 / 2);
			acceleration = ((forceGrav + dragy) / mass);
			
			if (useGravity) {
			//	acceleration.y += -9.81f;
			}
			velocity += acceleration * deltaTime;
			//cout << velocity.x << " " << velocity.y << " " << velocity.z <<  endl;
			position += velocity *  deltaTime;
			
		}
	}
	/* Applies full velocity change at once so not really accurate */
	void RigidBody::applyImpulse(vec3 force, float time)
	{
		acceleration = force / mass;
		velocity += acceleration * time;
	}


