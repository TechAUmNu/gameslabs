#pragma once

#include "../PhysicsLibrary/RigidBody.h"
#include "../MathsLibrary/vec4.h"
#include <vector>
#include <random>

class Boid : public RigidBody {
public:

	Boid(vec3 position);	

	/* Called every frame */
	void update(float deltaTime, Boid *boids[], int numberOfBoids);	
	
	/* Distance of this boid from another */
	float distanceFrom(Boid *boid);

	/* Colour of the boid*/
	vec4 colour;
protected:
	float neighbourCount;	

	/* Temp vector for distance calculations*/
	vec3* temp = new vec3(0,0,0);
	
	vec3 alignment;
	vec3 cohesion;
	vec3 separation;
	
	std::default_random_engine engine;	
	std::uniform_real_distribution<float> wanderGenerator;

};