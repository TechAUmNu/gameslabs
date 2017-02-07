#pragma once


#include "../PhysicsLibrary/PointMass.h";
#include "../MathsLibrary/vec4.h"

class Particle : public PointMass{
public:

	Particle(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass, float lifespan, vec4 colour, float fadeDelay, float fadeRate);

	void update(float deltaTime);

protected:
	vec3 position, velocity, force, friction;
	bool gravity;
	float mass;
	float lifespan;
	float fadeDelay, fadeRate;
	vec4 colour;
};