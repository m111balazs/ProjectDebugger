#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "graphics/animation.h"

typedef struct {
    float x, y;
    float vx, vy;
    int width, height;
    SDL_Texture* texture;
    Animation* animation;
    bool active;
    bool solid;
} Entity;

void Entity_Init(Entity* e, SDL_Texture* tex, float x, float y, int w, int h, bool solid);
void Entity_Update(Entity* e, float deltaTime);
void Entity_Render(Entity* e, SDL_Renderer* renderer, float camX, float camY);