#pragma once

#include <cstdint>
#include <unordered_map>

#include "glm/vec2.hpp"


struct Circle
{
    float radius;
};

struct AABB
{
    glm::vec2 halfBounds;
};

enum class ShapeType : uint8_t
{
    NONE = 0,
    CIRCLE = 1 << 0,
    AABB = 1 << 1
};

struct Shape
{
    ShapeType Type;

    union
    {
        Circle CircleData;
        AABB AABBData;
    };
};

using CollisionFunction = bool(*)(const glm::vec2&, const Shape&, const glm::vec2&, const Shape&);
using CollisionMap = std::unordered_map<ShapeType, CollisionFunction>;


bool CheckCircleCircleCollision(const glm::vec2& positionA, const Shape& shapeA, const glm::vec2& positionB, const Shape& shapeB);
bool CheckCircleCircleCollision(const glm::vec2& positionA, const Circle& circleA, const glm::vec2& positionB, const Circle& circleB);

bool CheckAABBAABBCollision(const glm::vec2& positionA, const Shape& shapeA, const glm::vec2& positionB, const Shape& shapeB);
bool CheckAABBAABBCollision(const glm::vec2& positionA, const AABB& boxA, const glm::vec2& positionB, const AABB& boxB);

bool CheckCircleAABBCollision(const glm::vec2& positionA, const Shape& shapeA, const glm::vec2& positionB, const Shape& shapeB);
bool CheckCircleAABBCollision(const glm::vec2& positionA, const Circle& shapeA, const glm::vec2& positionB, const AABB& boxB);

#pragma region Shape Collision
inline bool CheckCircleCircleCollision(const glm::vec2& positionA, const Shape& shapeA, const glm::vec2& positionB,
    const Shape& shapeB)
{
    return CheckCircleCircleCollision(positionA, shapeA.CircleData, positionB, shapeB.CircleData);
}

inline bool CheckCircleCircleCollision(const glm::vec2& positionA, const Circle& circleA, const glm::vec2& positionB,
    const Circle& circleB)
{
    return false;
}

inline bool CheckAABBAABBCollision(const glm::vec2& positionA, const Shape& shapeA, const glm::vec2& positionB,
    const Shape& shapeB)
{
    return CheckAABBAABBCollision(positionA, shapeA.AABBData, positionB, shapeB.AABBData);
}

inline bool CheckAABBAABBCollision(const glm::vec2& positionA, const AABB& boxA, const glm::vec2& positionB,
    const AABB& boxB)
{
    return false;
}

inline bool CheckCircleAABBCollision(const glm::vec2& positionA, const Shape& shapeA, const glm::vec2& positionB,
    const Shape& shapeB)
{
    return CheckCircleAABBCollision(positionA, shapeA.CircleData, positionB, shapeB.AABBData);
}

inline bool CheckCircleAABBCollision(const glm::vec2& positionA, const Circle& shapeA, const glm::vec2& positionB,
    const AABB& boxB)
{
    return false;
}
#pragma endregion
