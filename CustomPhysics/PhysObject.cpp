#include "PhysObject.h"

#include <raylib.h>

PhysObject::PhysObject() : position({0, 0}), velocity({0, 0}), acceleration({0, 0}), mass(1.0f), drag(0.0f), isAffectedByGravity(true), collisionShape(Shape())
{
}

PhysObject::PhysObject(float x, float y) : position({x, y}), velocity({0, 0}), acceleration({0, 0}), mass(1.0f), drag(0.0f), isAffectedByGravity(true), collisionShape(Shape())
{
}

void PhysObject::TickPhys(float delta)
{
    velocity += acceleration * delta;
    acceleration = {0, 0};

    position += velocity * delta;
}

void PhysObject::Draw() const
{
    switch (collisionShape.Type)
    {
    case ShapeType::NONE:
        DrawPixel(position.x, position.y, RED);
        break;
    case ShapeType::CIRCLE:
        DrawCircle(position.x, position.y, collisionShape.CircleData.radius, RED);
        break;
    case ShapeType::AABB:
        DrawRectangle(position.x, position.y, collisionShape.AABBData.halfBounds.x * 2, collisionShape.AABBData.halfBounds.y * 2, RED);
        // @todo this
        break;
    }
}

void PhysObject::AddAccel(glm::vec2 accel)
{
    acceleration += accel;
}

void PhysObject::AddVelocity(glm::vec2 vel)
{
    velocity += vel;
}

void PhysObject::AddForce(glm::vec2 force)
{
    acceleration += force / mass;
}

void PhysObject::AddImpulse(glm::vec2 impulse)
{
    velocity += impulse / mass;
}
