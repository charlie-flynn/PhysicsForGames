#include "World.h"

#include "PhysObject.h"
#include "raylib.h"

World::World() : AccumulatedFixedTime(0), TargetFixedStep(1.0f / 30.0f)
{
    PhysObjects = std::vector<std::shared_ptr<class PhysObject>>();
}

void World::Init()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    
    
    PhysObjects.push_back(std::make_shared<PhysObject>());
    
    OnInit();
}

void World::Tick()
{
    AccumulatedFixedTime += GetFrameTime();

    for (auto physObject : PhysObjects)
    {
        DrawCircle(physObject->position.x, physObject->position.y, 10, {255, 0, 0, 255});
    }

    OnTick();
}

void World::TickFixed()
{
    AccumulatedFixedTime -= TargetFixedStep;

    for (auto physObject : PhysObjects)
    {
        if (physObject->isAffectedByGravity)
            physObject->AddAccel({0, 9.81f});
        
        physObject->TickPhys(TargetFixedStep);
    }

    // @todo do physics here

    OnTickFixed();
}

void World::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

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
