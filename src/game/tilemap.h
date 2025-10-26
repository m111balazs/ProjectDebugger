#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int tileSize;

    int** layers;
    int layerCount;
    
    SDL_Texture** tiles;
    int tileCount;
} Tilemap;

bool Tilemap_Load(Tilemap* tm, SDL_Renderer* renderer, 
                const char** tileset, int tileCount, 
                int** layers, int layerCount, 
                int width, int height, int tileSize);
void Tilemap_Render(Tilemap* tm, SDL_Renderer* renderer);
void Tilemap_Destroy(Tilemap* tm);