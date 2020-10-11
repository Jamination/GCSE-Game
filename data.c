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
    ComponentTransform transform;
    ComponentSprite sprite;
} Player;

Player player;

#endif