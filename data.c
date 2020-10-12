#ifndef DATA_H
#define DATA_H

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
    Vector2 velocity, previousPos, projectedPos;
} ComponentPhysics;

typedef struct
{
    ComponentTransform transform;
    ComponentPhysics physics;
    ComponentHitbox hitbox;
    int moveSpeed, jumpHeight;
    float gravity;
} Player;

Player player;

#endif