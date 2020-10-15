#pragma once

#include "raylib.h"
#include "physac.h"

#define ScreenWidth 1280
#define ScreenHeight 720

typedef enum
{
    Undefined,
    MainMenuScreen,
    StartingScreen,
} ScreenType;

ScreenType CurrentScreen, NextScreen;

typedef struct
{
    float x, y;
    float scale, rotation;
} ComponentTransform;

typedef struct
{
    Texture2D texture;
    Color colour;
    Vector2 origin;
    bool centered;
} ComponentSprite;

typedef struct
{
    ComponentTransform transform;
    ComponentSprite sprite;
    int moveSpeed, jumpHeight;
    float gravity;
} Player;

Player player;
