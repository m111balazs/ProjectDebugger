#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct Texture {
    char name[128];
    SDL_Texture* sdlTexture;
} Texture;

bool TextureManager_Init(SDL_Renderer* renderer);
void TextureManager_Quit(void);

SDL_Texture* Texture_Load(const char* file);
void Texture_Unload(const char* file);