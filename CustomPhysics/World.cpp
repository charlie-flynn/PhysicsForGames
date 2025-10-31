#include "World.h"

#include <iostream>
#include <ostream>

#include "PhysObject.h"
#include "raylib.h"
#include "Util.h"

World::World() : AccumulatedFixedTime(0), TargetFixedStep(1.0f / 30.0f)
{
    PhysObjects = std::vector<std::shared_ptr<class PhysObject>>();

    collisionMap = CollisionMap();
}

void World::Init()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    collisionMap[ShapeType::CIRCLE | ShapeType::CIRCLE] = CheckCircleCircleCollision;
    collisionMap[ShapeType::AABB | ShapeType::AABB] = CheckAABBAABBCollision;
    collisionMap[ShapeType::CIRCLE | ShapeType::AABB] = CheckCircleAABBCollision;
    
    PhysObjects.push_back(std::make_shared<PhysObject>());
    
    OnInit();
}

void World::Tick()
{
    AccumulatedFixedTime += GetFrameTime();

    if (IsMouseButtonPressed(MouseButton::MOUSE_BUTTON_LEFT))
    {
        auto object = std::make_shared<PhysObject>(GetMouseX(), GetMouseY());
        object->collisionShape.Type = ShapeType::AABB;
        object->collisionShape.AABBData.halfBounds = {5.0f, 5.0f};
        PhysObjects.push_back(object);
    }

    OnTick();
}

void World::TickFixed()
{
    AccumulatedFixedTime -= TargetFixedStep;

    for (auto &physActorA : PhysObjects)
    {
        if (physActorA->collisionShape.Type == ShapeType::NONE)
            continue;
        
        for (auto &physActorB : PhysObjects)
        {
            if (physActorA == physActorB || physActorB->collisionShape.Type == ShapeType::NONE)
                continue;

            // checks if the second physactor's type's value is higher than the first, and reorders them accordingly for the collision check
            if (physActorB->collisionShape.Type > physActorA->collisionShape.Type
                ? collisionMap[physActorA->collisionShape.Type | physActorB->collisionShape.Type](physActorA->position, physActorA->collisionShape, physActorB->position, physActorB->collisionShape)
                : collisionMap[physActorA->collisionShape.Type | physActorB->collisionShape.Type](physActorB->position, physActorB->collisionShape, physActorA->position, physActorA->collisionShape))
            {
                std::cout << "Collision!" << std::endl;
            }
                
        }
    }

    for (auto physObject : PhysObjects)
    {
        if (physObject->isAffectedByGravity)
            physObject->AddAccel({0, 9.81f});
        
        physObject->TickPhys(TargetFixedStep);
    }
    OnTickFixed();
}

void World::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

for (auto physObject : PhysObjects)
{
    physObject->Draw();
}
    
    OnDraw();

    EndDrawing();
}

void World::Exit()
{
    OnExit();

    CloseWindow();        // Close window and OpenGL context
}

bool World::ShouldClose() const
{
    return WindowShouldClose();
}

bool World::ShouldTickFixed() const
{
    return AccumulatedFixedTime >= TargetFixedStep;
}
