#ifndef DATA_H
#define DATA_H

#include "raylib.h"

#define ScreenWidth 1280
#define ScreenHeight 720

typedef struct
{
    int x, y;
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
    Vector2 velocity, previousPos, projectedPos;
} ComponentPhysics;

typedef struct
{
    ComponentTransform transform;
    ComponentSprite sprite;
    ComponentPhysics physics;
    int moveSpeed;
} Player;

Player player;

#endif