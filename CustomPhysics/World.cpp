#include "World.h"

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
        PhysObjects.push_back(std::make_shared<PhysObject>(GetMouseX(), GetMouseY()));
    }

    OnTick();
}

void World::TickFixed()
{
    AccumulatedFixedTime -= TargetFixedStep;

    for (auto &physActorA : PhysObjects)
    {
        for (auto &physActorB : PhysObjects)
        {
            
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
