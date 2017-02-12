#include "Boid.h"
#include <iostream>
Boid::Boid(vec3 position) : RigidBody(position, vec3::zero(), vec3::zero(), material, 0, false, 1)
{
}

Boid::Boid() : RigidBody(vec3(0,0,-20), velocity, dragy, material, 0, false, 1)
{	
	position = vec3(0, 0, -20);
	velocity = vec3(1, 1, 1);
	dragy = vec3::zero();
}
	

// Called every frame
void Boid::update(float deltaTime, Boid boids[], int numberOfBoids) {
	
	vec3 alignment = computeAlignment(boids, numberOfBoids);
	vec3 cohesion = computeCohesion(boids, numberOfBoids);
	vec3 separation = computeSeparation(boids, numberOfBoids);

	velocity += alignment + cohesion + separation;	
	velocity.normalize(1);
	RigidBody::update(deltaTime);

}

vec3 Boid::computeAlignment(Boid boids[], int numberOfBoids)
{
	neighborCount = 0;
	vec3 v = vec3::zero();
	for (int i = 0; i < numberOfBoids; i++) {
		if (&boids[i] != this) {
			if (distanceFrom(boids[i]) < 30)
			{
				v += velocity;				
				neighborCount++;
			}
		}	
	}
	
	if (neighborCount == 0)
		return v;

	v /= neighborCount;	
	v.normalize(1);
	return v;
}

vec3 Boid::computeCohesion(Boid boids[], int numberOfBoids)
{
	neighborCount = 0;
	vec3 v = vec3::zero();
	for (int i = 0; i < numberOfBoids; i++) {
		if (&boids[i] != this) {
			if (distanceFrom(boids[i]) < 30)
			{
				v += position;				
				neighborCount++;
			}
		}
	}

	if (neighborCount == 0)
		return v;

	v /= neighborCount;	
	v -= position;
	v.normalize(1);
	return v;
}

vec3 Boid::computeSeparation(Boid boids[], int numberOfBoids)
{
	neighborCount = 0;
	vec3 v = vec3::zero();
	for (int i = 0; i < numberOfBoids; i++) {
		if (&boids[i] != this) {
			if (distanceFrom(boids[i]) < 3)
			{
				v += boids[i].position - position;				
				neighborCount++;
			}
		}
	}

	if (neighborCount == 0)
		return v;

	v /= neighborCount;	
	v *= -1;	
	v.normalize(1);
	return v;
}

float Boid::distanceFrom(Boid boid)
{
	return (boid.position - position).magnitude();
}

