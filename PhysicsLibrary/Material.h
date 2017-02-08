#pragma once

class Material {
public:

	Material(float staticFriction, float dynamicFriction, float coeffRestitution);

	// default constructor
	Material();
	~Material();

	float staticFriction, dynamicFriction;
	float coeffRestitution = 0.3f;

};