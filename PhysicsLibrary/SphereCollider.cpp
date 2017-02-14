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
	// If touching or below the surface then bounce
	if (position.y <= -8.0f) {		
		if (!penetrationBottom) {
			velocity.y = -(velocity.y * material.coeffRestitution);
			penetrationBottom = true;
		}
		if (position.y <= -8.0f) {
			float penetration = abs(-8.0f - position.y);			
			const float percent = 0.8; 
			const float slop = 0.000001; 
			velocity.y += (fmax(penetration - slop, 0.0f) / 0.1 )* percent;
		}
		if (velocity.magnitude() < 0.5f) {
			isKinematic = true;
		}
	}
	else {
		penetrationBottom = false;
	}

	if (position.y >= 8.0f) {
		if (!penetrationTop) {
			velocity.y = -(velocity.y * material.coeffRestitution);
			penetrationTop = true;
		}
		if (position.y >= 8.0f) {
			float penetration = abs(8.0f - position.y);
			const float percent = 0.8; 
			const float slop = 0.1; 
			position.y -= fmax(penetration - slop, 0.0f) * percent;
		}
	
	}
	else {
		penetrationTop = false;
	}

	if (position.x <= -10.0f) {
		if (!penetrationLeft) {
			velocity.x = -(velocity.x * material.coeffRestitution);
			penetrationLeft = true;
		}
		if (position.x <= -10.0f) {
			float penetration = abs(-10.0f - position.x);
			const float percent = 0.8;
			const float slop = 0.1; 
			position.x += fmax(penetration - slop, 0.0f) * percent;
		}
		
	}
	else {
		penetrationLeft = false;
	}

	if (position.x >= 10.0f) {
		if (!penetrationRight) {
			velocity.x = -(velocity.x * material.coeffRestitution);
			penetrationRight = true;
		}
		if(position.x >= 10.0f){
			float penetration = abs(10.0f - position.x);
			const float percent = 0.8; 
			const float slop = 0.1; 
			position.x -= fmax(penetration - slop, 0.0f) * percent;
		}
		
	}
	else {
		penetrationRight = false;
	}	
	
	RigidBody::update(deltaTime);
}
