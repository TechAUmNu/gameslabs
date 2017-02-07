#include "Particle.h"

Particle::Particle(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass, float lifespan, vec4 colour, float fadeDelay, float fadeRate) : RigidBody(pos, vel, force, frict, gravity, mass)
{
	this->lifespan = lifespan;
	this->colour = colour;
	this->fadeDelay = fadeDelay;
	this->fadeRate = fadeRate;
}

// Called every frame
void Particle::update(float deltaTime) {
	RigidBody::update(deltaTime);

	lifespan -= deltaTime;
	if (lifespan > 0) {
		RigidBody::update(deltaTime);
		if (fadeDelay < 0 && colour.w > 0) {
			colour.w -= fadeRate * deltaTime;
		}
		else {
			fadeDelay -= deltaTime;
		}
	}
	else {
		colour.w = 0;
	}
}



