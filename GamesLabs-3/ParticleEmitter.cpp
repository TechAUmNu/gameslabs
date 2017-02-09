#include "ParticleEmitter.h"
#include <random>
#include <iostream>

ParticleEmitter::ParticleEmitter(vec3 position, vec3 acceleration, std::pair<vec4, vec4> colourRange, std::pair<float, float> dragRange, std::pair<float, float> lifeTimeRange, float spawnRate, std::pair<vec3, vec3> velocityRange, bool gravity, std::pair<float, float> massRange)
{
	this->position = position;
	this->acceleration = acceleration;
	this->colourRange = colourRange;
	this->dragRange = dragRange;
	this->lifeTimeRange = lifeTimeRange;	
	this->spawnRate = spawnRate;
	this->velocityRange = velocityRange;
	this->gravity = gravity;
	this->massRange = massRange;
}

void ParticleEmitter::update(float deltaTime)
{
	int spawnAmount = spawnRate * deltaTime;

	std::vector<Particle>::iterator iter;
	for (iter = particles.begin(); iter != particles.end(); ) {
		if (!iter->alive)
			iter = particles.erase(iter);
		else {
			iter->update(deltaTime);
			++iter;
		}
	}

	

	emit(spawnAmount);
	std::cout << particles.size() << std::endl;
}

void ParticleEmitter::emit(int particleCount)
{
	
	std::default_random_engine engine;
	engine.seed(std::random_device{}());
	std::uniform_real_distribution<float> massRangeGenerator(massRange.first, massRange.second);
	std::uniform_real_distribution<float> dragRangeGenerator(dragRange.first, dragRange.second);
	std::uniform_real_distribution<float> lifeTimeRangeGenerator(lifeTimeRange.first, lifeTimeRange.second);		

	for (int i = 0; i < particleCount; i++) {
		particles.push_back(Particle(position, vec3::random(velocityRange), vec3::zero(), materialParticle, dragRangeGenerator(engine), gravity, massRangeGenerator(engine), lifeTimeRangeGenerator(engine), colourRange));
	}
}
