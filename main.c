#include "raylib.h"
#include "functions.c"

static void Load(void);
static void Update(void);
static void Draw(void);

void Load(void)
{
    LoadPlayer();
    LoadBoxes();
}

void Update(void)
{
    UpdatePlayer();
}

void Draw(void)
{
    DrawBoxes();
    DrawPlayer();
    DrawFPS(10, 10);
}

int main()
{
    InitWindow(ScreenWidth, ScreenHeight, "GCSE Game By James Heasman");
    SetTargetFPS(60);

    Load();

    while (!WindowShouldClose())
    {
        Update();
        BeginDrawing();
            ClearBackground(DARKBLUE);
            Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
