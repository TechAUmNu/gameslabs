#pragma once

#include "../MathsLibrary/vec3.h"
#include "Material.h"

class RigidBody{
public:	

	RigidBody(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass);
	
	void update(float deltaTime);
	
	vec3 position;
	bool useGravity = false;
	bool isKinematic = false;
	Material material;
	
protected:
	vec3 velocity, acceleration, force;
	// Gravity Toggle
	
	float mass = 1.0f;
	float drag = 0.1f;
};