#pragma once

#include "raylib.h"

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
    float width, height;
} ComponentHitbox;

typedef struct
{
    Texture2D texture;
    Color colour;
    Vector2 origin;
    bool centered;
} ComponentSprite;

typedef struct
{
    Vector2 velocity, lastPos, projectedPos;
} ComponentPhysics;

typedef struct
{
    ComponentTransform transform;
    ComponentSprite sprite;
    ComponentPhysics physics;
    ComponentHitbox hitbox;
    int moveSpeed, jumpHeight;
    float gravity;
} Player;

typedef struct
{
    ComponentTransform transform;
    ComponentHitbox hitbox;
    ComponentPhysics physics;
} TestBox;

Player player;
TestBox boxes[1];
