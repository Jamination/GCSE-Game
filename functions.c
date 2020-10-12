#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
    player = (Player){};

    player.transform.x = ScreenWidth * .5f;
    player.transform.y = ScreenHeight * .5f;
    player.transform.scale = .1f;

    player.hitbox.width = 12;
    player.hitbox.height = 18;

    player.moveSpeed = 1000;
    player.jumpHeight = -1500;
    player.gravity = 98;
}

void UpdatePlayer()
{
    player.physics.previousPos = (Vector2){player.transform.x, player.transform.y};

    Vector2 direction = (Vector2){};

    if (IsKeyDown(KEY_A))
        direction.x--;
    if (IsKeyDown(KEY_D))
        direction.x++;

    player.physics.velocity.x = Lerp(player.physics.velocity.x, direction.x * player.moveSpeed, .25f);
    player.physics.velocity.y += player.gravity;

    if (IsKeyPressed(KEY_W))
        player.physics.velocity.y = player.jumpHeight;

    if (IsKeyReleased(KEY_W) && player.physics.velocity.y < 0)
        player.physics.velocity.y *= .5f;

    player.transform.x += player.physics.velocity.x * GetFrameTime();
    player.transform.y += player.physics.velocity.y * GetFrameTime();

    player.transform.x = Clamp(player.transform.x, 0, ScreenWidth - player.hitbox.width);

    if (player.transform.y >= ScreenHeight - player.hitbox.height)
    {
        player.transform.y = ScreenHeight - player.hitbox.height;
        player.physics.velocity.y = 0;
    }
    else if (player.transform.y <= 0)
    {
        player.transform.y = 0;
        player.physics.velocity.y = 0;
    }

    player.physics.projectedPos = (Vector2){player.transform.x, player.transform.y};
    SetMousePosition(player.transform.x, player.transform.y);
}

#pragma endregion

#endif