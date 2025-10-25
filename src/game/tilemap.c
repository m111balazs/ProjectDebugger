#include "tilemap.h"
#include "camera.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern Camera* gCamera;

bool Tilemap_Load(Tilemap* map, SDL_Renderer* renderer, const char** tileset, int tileCount, const int* mapData, int width, int height, int tileSize) {
    map->width = width;
    map->height = height;
    map->tileSize = tileSize;
    map->tileCount = tileCount;
    map->tiles = SDL_malloc(tileCount * sizeof(SDL_Texture*));
    if (!map->tiles) { printf("Tilemap malloc failed\n"); return false; }

    printf("\n======= Loading Tiles =======\n");

    for (int i = 0; i < tileCount; i++) {
        map->tiles[i] = IMG_LoadTexture(renderer, tileset[i]);
        if (!map->tiles[i]) {
            printf("Failed to load tile %d from %s: %s\n", i, tileset[i], SDL_GetError());
            return false;
        } else {
            printf("Loaded tile %d: %s\n", i, tileset[i]);
        }
    }

    map->data = mapData;
    printf("====== Tilemap loaded successfully. ======\n\n");
    return true;
}

void Tilemap_Render(Tilemap* map, SDL_Renderer* renderer){
    int tileSize = map->tileSize;

    int startX = (int)(gCamera->x / tileSize) -1;
    int startY = (int)(gCamera->y / tileSize) -1;
    int endX = (int)((gCamera->x + gCamera->width) / tileSize) + 2;
    int endY = (int)((gCamera->y + gCamera->height) / tileSize) + 2;

    // Clamp map bounds
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > map->width) endX = map->width;
    if (endY > map->height) endY = map->height;

    // Render only visible tiles
    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            int tileIndex = map->data[y * map->width + x];
            if(tileIndex < 0 || tileIndex >= map->tileCount) continue;

            SDL_FRect dest = {
                (float)32 + (x * map->tileSize - gCamera->x),
                (float)32 + (y * map->tileSize - gCamera->y),
                (float)map->tileSize,
                (float)map->tileSize
            };

            SDL_RenderTexture(renderer, map->tiles[tileIndex], NULL, &dest);
        }   
    }
}

void Tilemap_Destroy(Tilemap* map){
    if(!map) return;

    for (int i = 0; i < map->tileCount; i++) SDL_DestroyTexture(map->tiles[i]);

    SDL_free(map->tiles);
}