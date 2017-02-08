#pragma once

#include "../MathsLibrary/vec3.h"
#include "Material.h"

class RigidBody{
public:	

	RigidBody(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass);
	
	void update(float deltaTime);
	void applyImpulse(vec3 force, float time);
	vec3 position, velocity, acceleration, force;;
	bool useGravity = false;
	bool isKinematic = false;
	Material material;
	
protected:
	
	vec3 dragy;
	
	float mass = 1.0f;
	float drag;
};