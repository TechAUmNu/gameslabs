#include "Boid.h"
#include <iostream>
#include <random>

#define desiredSeparation 4.0f
#define neighbordist 5.0f

Boid::Boid(vec3 position) : RigidBody(position, vec3::zero(), vec3::zero(), material, 0, false, 1)
{
}

Boid::Boid() : RigidBody(vec3(0,0,-20), velocity, dragy, material, 0, false, 0.5)
{	
	position = vec3(0, 0, -20);
	velocity = vec3(1, 1, 1);
	dragy = vec3::zero();
}
	

// Called every frame
void Boid::update(float deltaTime, Boid *boids[], int numberOfBoids) {
	float alignmentFactor = 0.025f;
	float cohesionFactor = 0.04f;
	float seperationFactor = 0.04f;
	float wanderFactor = 0.05f;

	std::default_random_engine engine;
	engine.seed(std::random_device{}());
	std::uniform_real_distribution<float> wanderGenerator(-1.0f, 1.0f);

	vec3 alignment;
	vec3 cohesion;
	vec3 separation;

	neighborCount = 0;
	vec3 vA = vec3::zero();
	vec3 vC = vec3::zero();
	vec3 vS = vec3::zero();
	for (int i = 0; i < numberOfBoids; i++) {
		if (boids[i] != this) {
			if (distanceFrom(boids[i]) < neighbordist)
			{
				vA += boids[i]->velocity;
				vC += boids[i]->position;
				vS += boids[i]->position - position;
				neighborCount++;
			}
		}
	}

	if (neighborCount == 0) {
		alignment = vA;
		cohesion = vC;
		separation = vS;
	}
	else {
		vA /= neighborCount;
		vA.normalize(1);
		alignment = vA;

		vC /= neighborCount;
		vC -= position;
		vC.normalize(1);
		cohesion = vC;


		vS /= neighborCount;
		vS *= -1;
		vS.normalize(1);
		separation = vS;
	}
	

	velocity += alignment * alignmentFactor + cohesion * cohesionFactor + separation * seperationFactor + wanderGenerator(engine) * wanderFactor;
	velocity.normalize(1);
	//std::cout << velocity.x << std::endl;
	velocity *= 5;
	


	float perspective = 10.0f;// *abs(position.z);

	if (position.x > 5 * perspective) {
		position.x = -5 * perspective;
	}
	if (position.x < -5 * perspective) {
		position.x = 5 * perspective;
	}
	
	if (position.y > 3 * perspective) {
		position.y = -3 * perspective;
	}
	if (position.y < -3 * perspective) {
		position.y = 3 * perspective;
	}

	if (position.z > -50) {
		position.z = -100;
	}
	if (position.z < -100) {
		position.z = -50;
	}
	RigidBody::update(deltaTime);

}

vec3 Boid::computeAlignment(Boid *boids[], int numberOfBoids)
{
	neighborCount = 0;
	vec3 v = vec3::zero();
	for (int i = 0; i < numberOfBoids; i++) {
		if (boids[i] != this) {
			if (distanceFrom(boids[i]) < neighbordist)
			{
				v += boids[i]->velocity;
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

vec3 Boid::computeCohesion(Boid *boids[], int numberOfBoids)
{
	neighborCount = 0;
	vec3 v = vec3::zero();
	for (int i = 0; i < numberOfBoids; i++) {
		if (boids[i] != this) {
			if (distanceFrom(boids[i]) < neighbordist)
			{
				v += boids[i]->position;				
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

vec3 Boid::computeSeparation(Boid *boids[], int numberOfBoids)
{
	neighborCount = 0;
	vec3 v = vec3::zero();
	
	for (int i = 0; i < numberOfBoids; i++) {
		if (boids[i] != this) {
			if (distanceFrom(boids[i]) < desiredSeparation)
			{
				v += boids[i]->position - position;
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

float Boid::distanceFrom(Boid *boid)
{
	vec3::subtractFast(temp, &boid->position, &position);
	return temp->magnitude();
}


float Boid::rotationX() {
	return acos(velocity.normalize(1).x);	
}

float Boid::rotationY() {
	return acos(velocity.normalize(1).z);
}

float Boid::rotationZ() {
	return acos(velocity.normalize(1).z);
}
