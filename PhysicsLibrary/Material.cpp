#include "Material.h"

Material::Material(float staticFriction, float dynamicFriction, float coeffRestitution)
{
	this->staticFriction = staticFriction;
	this->dynamicFriction = dynamicFriction;
	this->coeffRestitution = coeffRestitution;
}
