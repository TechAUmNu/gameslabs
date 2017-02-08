#include "SphereCollider.h"
#include <cmath>

#include <iostream>
using namespace std;
SphereCollider::SphereCollider(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass, float radius) : RigidBody(position, velocity, force, material, drag, gravity, mass)
{
	this->radius = radius;
}

void SphereCollider::update(float deltaTime)
{
	RigidBody::update(deltaTime);
	
	// If touching or below the floor then bounce
	if (position.y <= -8.0f) {		
		if (!penetration) {
			velocity.y = -(velocity.y * material.coeffRestitution);
			penetration = true;
		}
		if (abs(velocity.y) < 0.1f) {
			isKinematic = true;
		}
	}
	else {
		penetration = false;
	}
	

}
