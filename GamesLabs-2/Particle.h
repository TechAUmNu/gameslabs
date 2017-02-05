#pragma once

#include "PointMass.h";

class Particle : public PointMass{
public:

	Particle(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass, int lifespan);

	void update(float deltaTime);

protected:
	vec3 position, velocity, force, friction;
	bool gravity;
	float mass;
};