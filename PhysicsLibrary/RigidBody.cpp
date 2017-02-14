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
		
		/* If physic are acting on this object */
		if (!isKinematic) {
			if (velocity.y > 0) {
				dragForce.y = (velocity.y * velocity.y * -drag);
			}
			else {
				dragForce.y = (velocity.y * velocity.y * drag);
			}

			if (velocity.x > 0) {
				dragForce.x = (velocity.x * velocity.x * -drag);
			}
			else {
				dragForce.x = (velocity.x * velocity.x * drag);
			}

			if (velocity.z > 0) {
				dragForce.z = (velocity.z * velocity.z * -drag);
			}
			else {
				dragForce.z = (velocity.z * velocity.z * drag);
			}
			
			/* If gravity is enabled */
			if (useGravity) {
				vec3 forceGrav;
				forceGrav = vec3::zero();
				forceGrav.y = -9.81f * mass;
				acceleration = ((force + forceGrav + dragForce) / mass);
			}
			else {
				acceleration = ((dragForce) / mass);
			}			

			velocity += acceleration * deltaTime;
			position += velocity *  deltaTime;
			
		}
	}

	/* Applies full velocity change at once so not really accurate */
	void RigidBody::applyImpulse(vec3 force, float time)
	{
		acceleration = force / mass;
		velocity += acceleration * time;
	}


