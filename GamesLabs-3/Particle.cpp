#include "Particle.h"
#include <iostream>
Particle::Particle(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass, float lifespan, std::pair<vec4, vec4> colourRange) : RigidBody(position, velocity, force, material, drag, gravity, mass)
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
		RigidBody::update(deltaTime);
		colour.w = lifespanCount / lifespan;


		vec4 colourSpread = colourRange.second - colourRange.first;
		
		colour.x = colourRange.first.x + ((1.0f - (lifespanCount / lifespan)) * colourSpread.x);
		colour.y = colourRange.first.y + ((1.0f - (lifespanCount / lifespan)) * colourSpread.y);
		colour.z = colourRange.first.z + ((1.0f - (lifespanCount / lifespan)) * colourSpread.z);

		std::cout << (1.0f - (lifespanCount / lifespan)) * colourSpread.x << std::endl;
	}
	else {
		colour.w = 0;
		alive = false;
	}
}



