#include "tilemap.h"
#include "camera.h"
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern Camera* gCamera;

bool Tilemap_Load(Tilemap* tm, SDL_Renderer* renderer, const char** tileset, int tileCount, int** layers, int layerCount, int width, int height, int tileSize) {
    tm->width = width;
    tm->height = height;
    tm->tileSize = tileSize;
    tm->tileCount = tileCount;
    tm->layers = layers;
    tm->layerCount = layerCount;

    tm->tiles = malloc(sizeof(SDL_Texture*) * tileCount);
    if(!tm->tiles) return false; 

    printf("\n======= Loading Tiles =======\n");

    for (int i = 0; i < tileCount; i++) {
        tm->tiles[i] = IMG_LoadTexture(renderer, tileset[i]);
        if (!tm->tiles[i]) {
            printf("Failed to load tile %d from %s: %s\n", i, tileset[i], SDL_GetError());
            return false;
        } else {
            printf("Loaded tile %d: %s\n", i, tileset[i]);
        }
    }

    printf("====== Tilemap loaded successfully. ======\n\n");
    return true;
}

void Tilemap_Render(Tilemap* tm, SDL_Renderer* renderer){
    if (!tm || tm->layerCount <= 0) return;

    int startX = (int)(gCamera->x / tm->tileSize) -1;
    int startY = (int)(gCamera->y / tm->tileSize) -1;
    int endX = (int)((gCamera->x + gCamera->width) / tm->tileSize) + 1;
    int endY = (int)((gCamera->y + gCamera->height) / tm->tileSize) + 1;

    // Clamp map bounds
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > tm->width) endX = tm->width;
    if (endY > tm->height) endY = tm->height;

    // Render only visible tiles
    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            int id = tm->layers[0][y * tm->width + x];
            if(id < 0 || id >= tm->tileCount) continue;

            SDL_FRect dest = {
                (float)(x * tm->tileSize) - gCamera->x,
                (float)(y * tm->tileSize) - gCamera->y,
                (float)tm->tileSize,
                (float)tm->tileSize
            };

            SDL_RenderTexture(renderer, tm->tiles[id], NULL, &dest);
        }   
    }
}

void Tilemap_Destroy(Tilemap* map){
    if(!map) return;

    for (int i = 0; i < map->tileCount; i++) if(map->tiles[i]) SDL_DestroyTexture(map->tiles[i]);

    SDL_free(map->tiles);
}