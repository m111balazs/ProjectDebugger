#include "entity_manager.h"
#include <stdio.h>
#include <string.h>

void EntityManager_Init(EntityManager* mgr){
    printf("Initializing EntityManager...\n");
    memset(mgr, 0, sizeof(EntityManager));
    printf("EntityManager initialization done.\n");
}

Entity* EntityManager_Create(EntityManager* mgr, SDL_Texture* tex, float x, float y, int w, int h, bool solid){
    if(mgr->count >= MAX_ENTITIES) return NULL;
    Entity* e = &mgr->entities[mgr->count++];
    Entity_Init(e, tex, x, y, w, h, solid);
    return e;
}

void EntityManager_Update(EntityManager* mgr, float deltaTime){
    for (int i = 0; i < mgr->count; i++){
        Entity_Update(&mgr->entities[i], deltaTime);
    }
}

void EntityManager_Render(EntityManager* mgr, SDL_Renderer* renderer, float camX, float camY){
    for (int i = 0; i < mgr->count; i++){
        Entity* e = &mgr->entities[i];
        if (!e->active || !e->texture) continue;

        SDL_FRect dest = {
            e->x - camX,
            e->y - camX,
            (float)e->width,
            (float)e->height 
        };

        SDL_RenderTexture(renderer, e->texture, NULL, &dest);
    }
}