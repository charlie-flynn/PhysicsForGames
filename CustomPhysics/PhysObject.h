#pragma once

#include <glm/vec2.hpp>
#include "Shape.h"

class PhysObject
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	float mass;
	float drag;
	bool isAffectedByGravity;
	Shape collisionShape;

	PhysObject();
	PhysObject(float x, float y);

	void TickPhys(float delta);
	void Draw() const;

	void AddAccel(glm::vec2 accel);
	void AddVelocity(glm::vec2 vel);
	void AddForce(glm::vec2 force);
	void AddImpulse(glm::vec2 impulse);
};
