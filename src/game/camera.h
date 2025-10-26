#pragma once
#include <SDL3/SDL.h>
#include "game/tilemap.h"

typedef struct {
    float x, y;         
    float width, height;
    float targetX, targetY;
    float smoothSpeed;
    float offsetX, offsetY;
} Camera;

void Camera_Init (Camera* cam, float width, float height);
void Camera_Update (Camera* cam, float targetX, float targetY, float mapW, float mapH);