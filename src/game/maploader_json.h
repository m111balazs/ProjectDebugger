#pragma once
#include <stdbool.h>

typedef struct {
    int width;
    int height;
    int tileSize;
    int* data;
    float playerStartX;
    float playerStartY;
} JsonMap;

bool LoadMapFromJSON(const char* filename, JsonMap* outMap);
void FreeJsonMap(JsonMap* map);