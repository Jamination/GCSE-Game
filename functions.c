#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "raymath.h"
#include "data.c"

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
    player.transform.scale = .1f;
    player.transform.x = 0;
    player.transform.y = 0;
    player.sprite.centered = true;
}

void UpdatePlayer()
{

}

void DrawPlayer()
{
    DrawSprite(&player.sprite, &player.transform);
}

#endif