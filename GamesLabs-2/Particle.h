#pragma once


#include "../PhysicsLibrary/RigidBody.h"
#include "../MathsLibrary/vec4.h"

class Particle : public RigidBody{
public:

	Particle(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass, float lifespan, vec4 colour, float fadeDelay, float fadeRate);

	void update(float deltaTime);

protected:
	vec3 position, velocity, force, friction;
	bool gravity;
	float mass;
	float lifespan;
	float fadeDelay, fadeRate;
	vec4 colour;
};