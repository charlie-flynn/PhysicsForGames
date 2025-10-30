#include "PhysObject.h"

PhysObject::PhysObject() : position({0, 0}), velocity({0, 0}), acceleration({0, 0}), mass(1.0f), isAffectedByGravity(true)
{
}

void PhysObject::TickPhys(float delta)
{
    velocity += acceleration * delta;
    acceleration = {0, 0};
}

void PhysObject::AddForce(glm::vec2 force)
{
    acceleration += force * mass;
}
