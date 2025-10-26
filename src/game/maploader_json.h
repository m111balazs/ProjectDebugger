#pragma once
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int tileSize;

    int layerCount;
    int** layers;

    float playerStartX;
    float playerStartY;
} JsonMap;

bool LoadMapFromJSON(const char* filename, JsonMap* outMap);
void FreeJsonMap(JsonMap* map);