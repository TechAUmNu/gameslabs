#include "Material.h"

Material::Material(float staticFriction, float dynamicFriction, float coeffRestitution)
{
	this->staticFriction = staticFriction;
	this->dynamicFriction = dynamicFriction;
	this->coeffRestitution = coeffRestitution;
}

Material::Material()
{
	staticFriction = 0.5;
	dynamicFriction = 0.2;
	coeffRestitution = 0.3f;
}

Material::~Material()
{
}
