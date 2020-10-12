#ifndef MAIN_H
#define MAIN_H

#include "raylib.h"
#include "functions.c"

void Load()
{
    LoadPlayer();
}

void Update()
{
    UpdatePlayer();
}

void Draw()
{
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

#endif