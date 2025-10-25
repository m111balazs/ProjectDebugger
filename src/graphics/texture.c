#include "texture.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <string.h>

#define MAX_TEXTURES 128

static Texture textures[MAX_TEXTURES];
static int textureCount = 0;
static SDL_Renderer* globalRenderer = NULL;

bool TextureManager_Init(SDL_Renderer* renderer){
    printf("Initializing TextureManager...\n");
    globalRenderer = renderer;
    textureCount = 0;
    printf("Initializing TextureManager done\n");
    return true;
}

SDL_Texture* Texture_Load(const char* file){
    for (int i = 0; i < textureCount; i++)
    {
        if (strcmp(textures[i].name, file) == 0){
            return textures[i].sdlTexture;
        }
    }

    if (textureCount >= MAX_TEXTURES) {
        printf("TextureManager: Max texture limit reached\n");
        return NULL;
    }

    SDL_Texture* tex = IMG_LoadTexture(globalRenderer, file);
    if(!tex){
        printf("TextureManager: Failed to load %s: %s\n", file, SDL_GetError());
        return NULL;
    }

    strcpy(textures[textureCount].name, file);
    textures[textureCount].sdlTexture == tex;
    textureCount++;

    printf("TextureManaget: Loaded: %s\n", file);
    return tex;
}

void TextureUnload(const char* file){
    for(int i = 0; i < textureCount; i++){
        SDL_DestroyTexture(textures[i].sdlTexture);

        for (int j = i; j < textureCount - 1; j++)
        {
            textures[j] = textures[j + 1];
        }
        textureCount--;
        printf("TextureManager: File unloaded - %s\n", file);
        return;
    }
}

void TextureManager_Quit(void){
    for (int i = 0; i < textureCount; i++){
        SDL_DestroyTexture(textures[i].sdlTexture);
    }

    textureCount = 0;
    globalRenderer = NULL;
}