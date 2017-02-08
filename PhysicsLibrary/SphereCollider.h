#pragma once

#include "../PhysicsLibrary/RigidBody.h"
#include "../MathsLibrary/vec4.h"
#include "../PhysicsLibrary/Material.h"

class SphereCollider : public RigidBody {
public:

	SphereCollider(vec3 position, vec3 velocity, vec3 force, Material material, float drag, bool gravity, float mass, float radius);

	void update(float deltaTime);
	float radius;
	bool penetrationBottom = false, penetrationTop = false, penetrationLeft = false, penetrationRight = false;
protected:
	
	
	
};