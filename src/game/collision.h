#pragma once
#include <stdbool.h>
#include "game/tilemap.h"

bool Collision_IsTileSolid(int tileIndex);
bool Collision_Check(float newX, float newY, float spriteW, float spriteH, const Tilemap* tolemap);