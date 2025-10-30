#pragma once

#include <glm/vec2.hpp>

class PhysObject
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	float mass;
	bool isAffectedByGravity;

	PhysObject();

	void TickPhys(float delta);

	void AddAccel(glm::vec2 accel);
	void AddVelocity(glm::vec2 vel);
	void AddForce(glm::vec2 force);
	void AddImpulse(glm::vec2 impulse);
};
