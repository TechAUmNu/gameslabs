#pragma once
#include "../MathsLibrary/vec3.h"

class PointMass{
public:	

	PointMass(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass);
	
	void update(float deltaTime);

protected:
	vec3 position, velocity, force, friction;	
	bool gravity;
	float mass;
};