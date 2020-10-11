#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include "data.c"

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

void LoadPlayer()
{
    player = (Player){};

    player.sprite.texture = LoadTexture("Content/Sprites/Shit.png");
    player.sprite.colour = WHITE;
    player.sprite.centered = true;

    player.transform.x = 0;
    player.transform.y = 0;
    player.transform.scale = .1f;

    player.moveSpeed = 1000;
}

void UpdatePlayer()
{
    player.physics.previousPos = (Vector2){player.transform.x, player.transform.y};

    Vector2 acceleration = (Vector2){};

    if (IsKeyDown(KEY_A))
        acceleration.x--;
    if (IsKeyDown(KEY_D))
        acceleration.x++;
    if (IsKeyDown(KEY_W))
        acceleration.y--;
    if (IsKeyDown(KEY_S))
        acceleration.y++;
    
    if (!Vector2Equals(acceleration, Vector2Zero()))
        acceleration = Vector2Normalize(acceleration);

    player.physics.velocity = Vector2Lerp(player.physics.velocity, Vector2Multiply(acceleration, player.moveSpeed), .5f);

    player.transform.x += player.physics.velocity.x * GetFrameTime();
    player.transform.y += player.physics.velocity.y * GetFrameTime();
    player.physics.projectedPos = (Vector2){player.transform.x, player.transform.y};
}

void DrawPlayer()
{
    DrawSprite(&player.sprite, &player.transform);
}

#endif