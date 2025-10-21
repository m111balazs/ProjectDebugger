#include "tilemap.h"
#include "camera.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

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
    printf("Tilemap loaded successfully.\n");
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