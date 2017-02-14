#pragma once


#include "../PhysicsLibrary/RigidBody.h"
#include "../MathsLibrary/vec4.h"
#include <vector>

class Particle : public RigidBody {
public:

	Particle(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass, float lifespan, std::pair<vec4, vec4> colourRange);

	void update(float deltaTime);
	vec4 colour;
	bool alive = true;
protected:		
	float lifespan, lifespanCount;
	std::pair<vec4, vec4> colourRange;
	
};