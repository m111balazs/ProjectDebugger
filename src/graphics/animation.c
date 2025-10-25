#include "animation.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

bool Animation_Load(Animation* anim, SDL_Renderer* renderer, const char* file, int frameWidth, int frameHeight, int frameCount, int fps){
    printf("Loading animation for (%d)...\n", file);
    anim->texture = IMG_LoadTexture(renderer, file);
    if(!anim->texture){
        printf("Animation: Failed to load %s: %s\n", file, SDL_GetError());
        return false;
    }

    anim->frameWidth = frameWidth;
    anim->frameHeight = frameHeight;
    anim->frameCount = frameCount;
    anim->currentFrame = 0;
    anim->frameTime = 1.0f / fps;
    anim->timeAccumulator = 0.0f;
    printf("Loaded file (%d)\n", file);
    return true;
}

void Animation_Update(Animation* anim, float deltaTime){
    anim->timeAccumulator += deltaTime;
    if (anim->timeAccumulator >= anim->frameTime){
        anim->timeAccumulator -= anim->frameTime;
        anim->currentFrame++;
        if (anim->currentFrame >= anim->frameCount) anim->currentFrame = 0;
    } 
}

void Animation_Render(Animation* anim, SDL_Renderer* renderer, float x, float y){
    SDL_FRect src = {
        (float)anim->currentFrame * anim->frameWidth,
        0.0f,
        (float)anim->frameWidth,
        (float)anim->frameHeight
    };

    SDL_FRect dest = { x, y, (float)anim->frameWidth, (float)anim->frameHeight };
    SDL_RenderTexture(renderer, anim->texture, &src, &dest);
}

void Animation_Destroy(Animation* anim){
    printf("Destroying animation (%d)\n", anim);
    if (anim->texture) { SDL_DestroyTexture(anim->texture); printf("Animation destroyed (%d)\n", anim); }
    printf("Animation cant be destroyed (%d)\n", anim);
}