#include "tilemap.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

bool Tilemap_Load(Tilemap* map, SDL_Renderer* renderer, const char* tileset[], int tileCount, const int* data, int width, int height, int tileSize) {
    map->width = width;
    map->height = height;
    map->tileSize = tileSize;
    map->tileCount = tileCount;
    map->data = (int*)malloc(sizeof(int) * width * height);
    if (!map->data) return false;

    // Copy map data
    for (int i = 0; i < width * height; i++){
        map->data[i] = data[i];
    }

    // Load tile textures
    for (int i = 0; i < tileCount; i++){
        map->tiles[i] = IMG_LoadTexture(renderer, tileset[i]);
        if (!map->tiles[i]) {
            printf("Tilemap: Failed to load %s\n", tileset[i]);
            return false;
        }
    }

    return true;
}

void Tilemap_Render(Tilemap* map, SDL_Renderer* renderer){
    for (int y = 0; y < map->height; y++)
    {
        for (int x = 0; x < map->width; x++)
        {
            int tileIndex = map->data[y * map->width + x];
            if(tileIndex < 0 || tileIndex >= map->tileCount) continue;

            SDL_FRect dest = {
                (float)(x * map->tileSize),
                (float)(y * map->tileSize),
                (float)map->tileSize,
                (float)map->tileSize
            };

            SDL_RenderTexture(renderer, map->tiles[tileIndex], NULL, &dest);
        }   
    }
}

void Tilemap_Destroy(Tilemap* map){
    for (int i = 0; i < map->tileCount; i++) SDL_DestroyTexture(map->tiles[i]);

    free(map->tiles);
    free(map->data);
}