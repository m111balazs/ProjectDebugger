#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int tileSize;
    int* data;
    SDL_Texture** tiles;
    int tileCount;
} Tilemap;

bool Tilemap_Load(Tilemap* map, SDL_Renderer* renderer, const char** tileset, int tileCount, const int* mapData, int width, int height, int tileSize);
void Tilemap_Render(Tilemap* tilemap, SDL_Renderer* renderer);
void Tilemap_Destroy(Tilemap* Tilemap);