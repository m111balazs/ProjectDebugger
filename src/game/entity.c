#include "entity.h"

void Entity_Init(Entity* e, SDL_Texture* tex, float x, float y, int w, int h, bool solid){
    e->x = x;
    e->y = y;
    e->vx = 0;
    e->vy = 0;
    e->width = w;
    e->height = h;
    e->texture = tex;
    e->solid = solid;
    e->active = true;
}

void Entity_Update(Entity* e, float deltaTime){
    if (!e->active) return;

    e->x += e->vx * deltaTime;
    e->y += e->vy * deltaTime;
}

void Entity_Render(Entity* e, SDL_Renderer* renderer, float camX, float camY){
    if(!e->active || e->texture) return;

    SDL_FRect dest = {
        e->x - camX,
        e->y - camY,
        (float)e->width,
        (float)e->height
    };

    SDL_RenderTexture(renderer, e->texture, NULL, &dest);
}