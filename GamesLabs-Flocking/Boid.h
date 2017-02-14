#pragma once

#include "../PhysicsLibrary/RigidBody.h"
#include "../MathsLibrary/vec4.h"
#include <vector>

class Boid : public RigidBody {
public:

	Boid(vec3 position);	
	Boid();


	void update(float deltaTime, Boid *boids[], int numberOfBoids);

	vec3 computeAlignment(Boid *boids[], int numberOfBoids);

	
	vec3 computeCohesion(Boid *boids[], int numberOfBoids);
	vec3 computeSeparation(Boid *boids[], int numberOfBoids);
	float distanceFrom(Boid *boid);

	float rotationX();
	float rotationY();
	float rotationZ();
protected:
	float neighborCount;	
};