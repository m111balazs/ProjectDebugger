#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool IsTileSolid(int tileID) {
    return (tileID == 1 || tileID == 2 || tileID == 3);
}

void FindRandomSpawn(const Tilemap* map, float* outX, float* outY){
    srand((unsigned int)time(NULL));

    int w = map->width;
    int h = map->height;

    while(1){
        int tx = rand() % w;
        int ty = rand() % h;
        int index = map->layers[0][ty * w + tx];

        bool hasNeighbor = false;
        if (ty > 0 && !IsTileSolid(map->layers[0][(ty - 1) * w + tx])) hasNeighbor = true;
        if (ty < h - 1 && !IsTileSolid(map->layers[0][(ty + 1) * w + tx])) hasNeighbor = true;
        if (tx > 0 && !IsTileSolid(map->layers[0][ty * w + (tx - 1)])) hasNeighbor = true;
        if (tx < w - 1 && !IsTileSolid(map->layers[0][ty * w + (tx + 1)])) hasNeighbor = true;

        if (hasNeighbor) {
            *outX = tx * map->tileSize + map->tileSize / 2.0f - 16.0f;
            *outY = ty * map->tileSize + map->tileSize / 2.0f - 16.0f;
            return;
        }
    }
}