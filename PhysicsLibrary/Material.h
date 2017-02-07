#pragma once

class Material {
public:

	Material(float staticFriction, float dynamicFriction, float coeffRestitution);

	float staticFriction, dynamicFriction;
	float coeffRestitution = 0.3f;

};