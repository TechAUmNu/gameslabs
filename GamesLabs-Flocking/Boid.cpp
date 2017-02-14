#include "Boid.h"
#include <iostream>
#include <random>

/* Boid rule factors */
#define NEIGHBOURHOOD_DIST 5.0f
#define ALIGNMENT_FACTOR 0.025f
#define COHESION_FACTOR 0.04f
#define SEPERATION_FACTOR 0.04f
#define WANDER_FACTOR 0.01f
#define MAX_VELOCITY 5.0f

Boid::Boid(vec3 position) : RigidBody(position, vec3::zero(), vec3::zero(), material, 0, false, 1)
{
	/* Random wander */
	engine.seed(std::random_device{}());
	wanderGenerator = std::uniform_real_distribution<float>(-1.0f, 1.0f);
}
	

/* Called every frame */
void Boid::update(float deltaTime, Boid *boids[], int numberOfBoids) {
	
	/* Reset variables */
	neighbourCount = 0;
	alignment.set(0, 0, 0);
	cohesion.set(0, 0, 0);
	separation.set(0, 0, 0);
	
	/* Optimized Boid rules calculations*/
	for (int i = 0; i < numberOfBoids; i++) {
		if (boids[i] != this) {
			if (distanceFrom(boids[i]) < NEIGHBOURHOOD_DIST)
			{
				alignment += boids[i]->velocity;
				cohesion += boids[i]->position;
				separation += boids[i]->position - position;
				neighbourCount++;
			}
		}
	}
	
	if (neighbourCount != 0) {		
		alignment /= neighbourCount;
		alignment.normalize(1);		
		
		cohesion /= neighbourCount;
		cohesion -= position;
		cohesion.normalize(1);

		separation /= neighbourCount;
		separation *= -1;
		separation.normalize(1);		
	}	

	/* Calculate velocity change based on flocking rules and factors */
	velocity += alignment * ALIGNMENT_FACTOR + cohesion * COHESION_FACTOR + separation * SEPERATION_FACTOR + wanderGenerator(engine) * WANDER_FACTOR;
	
	/* Normalize to get back to direction vector*/
	velocity.normalize(1);

	/* Constant velocity */
	velocity *= MAX_VELOCITY;
	
	/* Wrapping */
	if (position.x > 50) {
		position.x = -50;
	}
	if (position.x < -50) {
		position.x = 50;
	}
	
	if (position.y > 30) {
		position.y = -30;
	}
	if (position.y < -30) {
		position.y = 30;
	}

	if (position.z > -50) {
		position.z = -100;
	}
	if (position.z < -100) {
		position.z = -50;
	}
	/* Update the underlying RigidBody */
	RigidBody::update(deltaTime);

}

/* Distance of this boid from another */
float Boid::distanceFrom(Boid *boid)
{
	vec3::subtractFast(temp, &boid->position, &position);
	return temp->magnitude();
}
