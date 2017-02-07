#pragma once
#include "../MathsLibrary/vec3.h"

class PointMass{
public:	

	PointMass(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass);
	
	void update(float deltaTime);

protected:
	vec3 position, velocity, acceleration, force, friction;
	// Gravity Toggle
	bool gravity = false;
	float coeffRestitution = 0.3f;
	float mass = 1.0f;
};