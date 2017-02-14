#pragma once

#include "../MathsLibrary/vec3.h"
#include "../MathsLibrary/vec4.h"
#include "Particle.h"
#include <utility>
#include <vector>
#include "../PhysicsLibrary/Material.h"


class ParticleEmitter {
public:

	ParticleEmitter(vec3 position, vec3 acceleration, std::pair<vec4, vec4> colourRange, std::pair<float, float> dragRange, std::pair<float, float> lifeTimeRange, float spawnRate, std::pair<vec3, vec3> velocityRange, bool gravity, std::pair<float, float> massRange);

	void update(float deltaTime);

	void emit(int particleCount);

	vec3 position;
	std::vector<Particle> particles;
protected:

	
	vec3 acceleration;
	bool gravity;
	std::pair<float, float> massRange, dragRange, lifeTimeRange, fadeDelayRange, fadeRateRange;
	std::pair<vec3, vec3> velocityRange;
	std::pair<vec4, vec4> colourRange;	
	float spawnRate;
	Material materialParticle = Material(0.8, 0.6, 0.4);
	
};