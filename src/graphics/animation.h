#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Texture* texture;
    int frameWidth;
    int frameHeight;
    int frameCount;
    int currentFrame;
    float frameTime;
    float timeAccumulator;
} Animation;

bool Animation_Load(Animation* anim, SDL_Renderer* renderer, const char* file, int frameWidth, int frameHeight, int frameCount, int fps);
void Animation_Update(Animation* anim, float deltaTime);
void Animation_Render(Animation* anim, SDL_Renderer* renderer, float x, float y);
void Animation_Destroy(Animation* anim);