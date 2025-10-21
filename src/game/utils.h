#pragma "once"
#include "game/tilemap.h"
#include <stdbool.h>

bool IsTileSolid(int tileID);

void FindRandomSpawn(const Tilemap* map, float* outX, float* outY);