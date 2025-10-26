#include "maploader_json.h"
#include "../external/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool LoadMapFromJSON(const char* filename, JsonMap* outMap)
{
    printf("📄 Loading JSON map: %s\n", filename);

    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("❌ Failed to open JSON map file: %s\n", filename);
        return false;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* jsonText = malloc(length + 1);
    if (!jsonText) {
        printf("❌ Memory allocation failed for JSON text.\n");
        fclose(file);
        return false;
    }

    fread(jsonText, 1, length, file);
    jsonText[length] = '\0';
    fclose(file);

    cJSON* root = cJSON_Parse(jsonText);
    if (!root) {
        printf("❌ JSON parse error — check file syntax.\n");
        free(jsonText);
        return false;
    }

    // --- Core map info ---
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

    // --- Layers ---
    cJSON* layers = cJSON_GetObjectItem(root, "layers");
    if (!layers || !cJSON_IsArray(layers)) {
        printf("⚠️  No 'layers' array found in map — loading as single-layer fallback.\n");

        // fallback to a single-layer layout
        outMap->layerCount = 1;
        outMap->layers = malloc(sizeof(int*));
        outMap->layers[0] = NULL;
    } else {
        int layerCount = cJSON_GetArraySize(layers);
        outMap->layerCount = layerCount;
        outMap->layers = malloc(sizeof(int*) * layerCount);

        printf("✅ Found %d layer(s)\n", layerCount);

        for (int l = 0; l < layerCount; l++) {
            cJSON* layer = cJSON_GetArrayItem(layers, l);
            cJSON* name = cJSON_GetObjectItem(layer, "name");
            const char* layerName = name ? name->valuestring : "(unnamed)";
            cJSON* dataArray = cJSON_GetObjectItem(layer, "data");

            if (!dataArray || !cJSON_IsArray(dataArray)) {
                printf("⚠️  Layer '%s' missing or invalid — skipping\n", layerName);
                outMap->layers[l] = NULL;
                continue;
            }

            int width = outMap->width;
            int height = outMap->height;
            int* layerData = malloc(sizeof(int) * width * height);
            if (!layerData) {
                printf("❌ Out of memory for layer '%s'\n", layerName);
                outMap->layers[l] = NULL;
                continue;
            }

            int y = 0;
            cJSON* row = NULL;
            cJSON_ArrayForEach(row, dataArray) {
                if (!cJSON_IsArray(row)) continue;
                int x = 0;
                cJSON* tile = NULL;
                cJSON_ArrayForEach(tile, row) {
                    if (x < width && y < height) {
                        layerData[y * width + x] = tile->valueint;
                    }
                    x++;
                }
                y++;
            }

            if (y == 0) {
                printf("⚠️  Layer '%s' appears empty.\n", layerName);
            } else {
                printf("✅ Loaded layer '%s' (%dx%d)\n", layerName, width, height);
            }

            outMap->layers[l] = layerData;
        }
    }

    printf("✅ Map loaded successfully: %dx%d (tileSize=%d)\n",
           outMap->width, outMap->height, outMap->tileSize);

    cJSON_Delete(root);
    free(jsonText);
    return true;
}

void FreeJsonMap(JsonMap* map)
{
    if (!map) return;

    if (map->layers) {
        for (int i = 0; i < map->layerCount; i++) {
            if (map->layers[i]) free(map->layers[i]);
        }
        free(map->layers);
        map->layers = NULL;
    }
}
