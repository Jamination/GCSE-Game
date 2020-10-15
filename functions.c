#pragma once

#include "raylib.h"
#include "raymath.h"
#include "data.c"

#pragma region HelperMethods

bool Vector2Equals(Vector2 a, Vector2 b)
{
    return a.x == b.x && a.y == b.y;
}

Vector2 Vector2Multiply(Vector2 a, float b)
{
    return (Vector2){a.x * b, a.y * b};
}

void DrawSprite(ComponentSprite* sprite, ComponentTransform* transform)
{
    Vector2 centerOrigin = {};

    if (sprite->centered)
        centerOrigin = (Vector2){sprite->texture.width * .5f, sprite->texture.height * .5f};

    DrawTexturePro(
    sprite->texture,
     (Rectangle){0, 0, sprite->texture.width, sprite->texture.height},
      (Rectangle) {transform->x, transform->y,
       sprite->texture.width * transform->scale, sprite->texture.height * transform->scale},
        Vector2Add(sprite->origin, Vector2MultiplyV(centerOrigin, (Vector2){transform->scale, transform->scale})), transform->rotation * RAD2DEG, sprite->colour
    );
}

#pragma endregion

#pragma region Player

void LoadPlayer()
{
    player = (Player)
    {
        .transform = (ComponentTransform)
        {
            .x = ScreenWidth * .5f,
            .y = ScreenHeight * .5f,
            .scale = .5f,
            .rotation = 0
        },
        .sprite = (ComponentSprite)
        {
            .texture =  LoadTexture("Content/Sprites/Shit.png"),
            .centered = true,
            .colour = WHITE,
        },
        .gravity = 98,
        .jumpHeight = -1500,
        .moveSpeed = 1000,
    };
}

void UpdatePlayer()
{

}

void DrawPlayer()
{
    DrawSprite(&player.sprite, &player.transform);
}

#pragma endregion
