#pragma once
#include "entity.h"

#define MAX_ENTITIES 256

typedef struct {
    Entity entities[MAX_ENTITIES];
    int count;
} EntityManager;

void EntityManager_Init(EntityManager* mgr);
Entity* EntityManager_Create(EntityManager* mgr, SDL_Texture* tex, float x, float y, int w, int h, bool solid);
void EntityManager_Update(EntityManager* mgr, float deltaTime);
void EntityManager_Render(EntityManager* mgr, SDL_Renderer* renderer, float camX, float camY);