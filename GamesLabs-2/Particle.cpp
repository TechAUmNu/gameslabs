
#include "../MathsLibrary/vec3.h"
#include "../MathsLibrary/vec4.h"
#include "PointMass.h"

class Particle : public PointMass {
public:
	
	// Time before particle is removed
	float lifespan;
	float fadeDelay, fadeRate;
	
	vec4 colour;

	Particle(vec3 pos, vec3 vel, vec3 force, vec3 frict, bool gravity, float mass, float lifespan, vec4 colour, float fadeDelay, float fadeRate) : PointMass(pos, vel, force, frict, gravity, mass)
	{
		this->lifespan = lifespan;
		this->colour = colour;		
		this->fadeDelay = fadeDelay;
		this->fadeRate = fadeRate;
	}	

	// Called every frame
	void update(float deltaTime) {
		PointMass::update(deltaTime);

		lifespan -= deltaTime;
		if (lifespan > 0) {
			PointMass::update(deltaTime);
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
};