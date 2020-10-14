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
    player = (Player){};

    player.transform.x = ScreenWidth * .5f;
    player.transform.y = ScreenHeight * .5f;
    player.transform.scale = .1f;

    player.sprite.texture = LoadTexture("Content/Sprites/Shit.png");
    player.sprite.colour = WHITE;
    player.sprite.centered = true;

    player.hitbox.width = 96;
    player.hitbox.height = 96;

    player.moveSpeed = 1000;
    player.jumpHeight = -1500;
    player.gravity = 98;
}

void UpdatePlayer()
{
    player.physics.lastPos = (Vector2){player.transform.x, player.transform.y};

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

    player.physics.projectedPos = (Vector2){player.transform.x, player.transform.y};

    player.physics.projectedPos.x += player.physics.velocity.x * GetFrameTime();
    player.physics.projectedPos.y += player.physics.velocity.y * GetFrameTime();

    player.physics.projectedPos.x = Clamp(player.physics.projectedPos.x, player.hitbox.width * .5f, ScreenWidth - player.hitbox.width * .5f);

    if (player.physics.projectedPos.y >= ScreenHeight - player.hitbox.height * .5f)
    {
        player.physics.projectedPos.y = ScreenHeight - player.hitbox.height * .5f;
        player.physics.velocity.y = 0;
    }
    else if (player.physics.projectedPos.y <= -player.hitbox.width * .5f)
    {
        player.physics.projectedPos.y = -player.hitbox.width * .5f;
        player.physics.velocity.y = 0;
    }

    #pragma region PlayerCollision

    Rectangle prevPlayerBounds = (Rectangle)
    {
        player.transform.x - player.hitbox.width * .5f * player.transform.scale,
        player.transform.y - player.hitbox.height * .5f * player.transform.scale,
        player.hitbox.width * player.transform.scale, player.hitbox.height * player.transform.scale
    };

    Rectangle projectedPlayerBounds = (Rectangle)
    {
        player.physics.projectedPos.x - player.hitbox.width * .5f * player.transform.scale,
        player.physics.projectedPos.y - player.hitbox.height * .5f * player.transform.scale,
        player.hitbox.width * player.transform.scale, player.hitbox.height * player.transform.scale
    };

    for (int i = 0; i < sizeof(boxes) / sizeof(TestBox); i++)
    {
        Rectangle boxBounds = (Rectangle){boxes[i].transform.x, boxes[i].transform.y, boxes[i].hitbox.width, boxes[i].hitbox.width};

        if (CheckCollisionRecs(projectedPlayerBounds, boxBounds))
        {
            Rectangle overlapX = GetCollisionRec((Rectangle){projectedPlayerBounds.x, prevPlayerBounds.y, projectedPlayerBounds.width, projectedPlayerBounds.height}, boxBounds);
            Rectangle overlapY = GetCollisionRec((Rectangle){prevPlayerBounds.x, projectedPlayerBounds.y, projectedPlayerBounds.width, projectedPlayerBounds.height}, boxBounds);

            if (boxes[i].transform.x > player.transform.x)
            {
                player.physics.projectedPos.x -= overlapX.width;
                player.physics.velocity.x = 0;
            }
            else
            {
                player.physics.projectedPos.x += overlapX.width;
                player.physics.velocity.x = 0;
            }

            if (boxes[i].transform.y > player.transform.y)
            {
                player.physics.projectedPos.y -= overlapY.height;
                player.physics.velocity.y = 0;
            }
            else
            {
                player.physics.projectedPos.y += overlapY.height;
                player.physics.velocity.y = 0;
            }
        }
    }

    #pragma endregion

    player.transform.x = player.physics.projectedPos.x;
    player.transform.y = player.physics.projectedPos.y;
}

void DrawPlayer()
{
    DrawSprite(&player.sprite, &player.transform);
}

#pragma endregion

#pragma region Boxes

void LoadBoxes()
{
    for (int i = 0; i < sizeof(boxes) / sizeof(TestBox); i++)
    {
        boxes[i].hitbox.width = 128;
        boxes[i].hitbox.height = 128;

        boxes[i].transform.x = ScreenWidth * .5f - 256;
        boxes[i].transform.y = ScreenHeight - 256;
    }
}

void DrawBoxes()
{
    for (int i = 0; i < sizeof(boxes) / sizeof(TestBox); i++)
    {
        DrawRectangle(boxes[i].transform.x, boxes[i].transform.y, boxes[i].hitbox.width, boxes[i].hitbox.height, BLACK);
    }
}

#pragma endregion
