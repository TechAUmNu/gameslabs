#include "Particle.h"
#include <iostream>
Particle::Particle(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass, float lifespan, std::pair<vec4, vec4> colourRange) : SphereCollider(position, velocity, force, material, drag, gravity, mass, mass)
{
	this->lifespan = lifespan;
	this->lifespanCount = lifespan;
	this->colourRange = colourRange;
	colour = colourRange.first;

}

// Called every frame
void Particle::update(float deltaTime) {
	//std::cout << lifespanCount << std::endl;
	if (lifespanCount > 0) {
		lifespanCount -= deltaTime;
		SphereCollider::update(deltaTime);
		colour.w = lifespanCount / lifespan;
		//std::cout << colour.w << std::endl;
	}
	else {
		colour.w = 0;
		alive = false;
	}
}



