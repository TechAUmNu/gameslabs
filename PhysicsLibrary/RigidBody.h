#pragma once
#include "../MathsLibrary/vec3.h"

class RigidBody{
public:	

	RigidBody(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass);
	
	void update(float deltaTime);

protected:
	vec3 position, velocity, acceleration, force, friction;
	// Gravity Toggle
	bool useGravity = false;
	
	float mass = 1.0f;
	float drag = 0.1f;
};