#include "maploader_json.h"
#include "../external/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool LoadMapFromJSON(const char* filename, JsonMap* outMap)
{
    printf("Loading JSON map from file (%d)...\n", filename);
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Failed to open JSON map: %s\n", filename);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* jsonText = malloc(length + 1);
    fread(jsonText, 1, length, file);
    jsonText[length] = '\0';
    fclose(file);

    cJSON* root = cJSON_Parse(jsonText);
    if (!root) {
        printf("JSON parse error\n");
        free(jsonText);
        return false;
    }

    // --- Read core map data ---
    outMap->width = cJSON_GetObjectItem(root, "width")->valueint;
    outMap->height = cJSON_GetObjectItem(root, "height")->valueint;
    outMap->tileSize = cJSON_GetObjectItem(root, "tileSize")->valueint;

    // --- Optional player start ---
    cJSON* player = cJSON_GetObjectItem(root, "player_start");
    if (player) {
        outMap->playerStartX = (float)cJSON_GetObjectItem(player, "x")->valuedouble;
        outMap->playerStartY = (float)cJSON_GetObjectItem(player, "y")->valuedouble;
    } else {
        outMap->playerStartX = 0;
        outMap->playerStartY = 0;
    }

    // --- Load first layer’s data array ---
    cJSON* layers = cJSON_GetObjectItem(root, "layers");
    if (!layers || !cJSON_IsArray(layers)) {
        printf("No 'layers' array found in map file\n");
        cJSON_Delete(root);
        free(jsonText);
        return false;
    }

    cJSON* firstLayer = cJSON_GetArrayItem(layers, 0);
    cJSON* dataArray = cJSON_GetObjectItem(firstLayer, "data");

    if (!dataArray || !cJSON_IsArray(dataArray)) {
        printf("Invalid or missing 'data' field in layer\n");
        cJSON_Delete(root);
        free(jsonText);
        return false;
    }

    int width = outMap->width;
    int height = outMap->height;
    int* mapData = malloc(sizeof(int) * width * height);
    if (!mapData) {
        printf("Out of memory for map\n");
        cJSON_Delete(root);
        free(jsonText);
        return false;
    }

    int y = 0;
    cJSON* row = NULL;
    cJSON_ArrayForEach(row, dataArray) {
        if (!cJSON_IsArray(row)) continue;

        int x = 0;
        cJSON* tile = NULL;
        cJSON_ArrayForEach(tile, row) {
            if (x < width && y < height) {
                mapData[y * width + x] = tile->valueint;
            }
            x++;
        }
        y++;
    }

    outMap->data = mapData;

    printf("Loaded JSON map: %dx%d (tileSize=%d)\n",
           outMap->width, outMap->height, outMap->tileSize);

    cJSON_Delete(root);
    free(jsonText);
    return true;
}

void FreeJsonMap(JsonMap* map)
{
    if (map && map->data) {
        free(map->data);
        map->data = NULL;
    }
}
