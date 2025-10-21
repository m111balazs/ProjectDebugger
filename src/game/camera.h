#pragma once
#include <SDL3/SDL.h>
#include "game/tilemap.h"

typedef struct {
    float x, y;         // top left corner of camera in world space
    float width, height;// veiwport size (same as window)
} Camera;

void Camera_Init (Camera* cam, float width, float height);
void Camera_Update (Camera* cam, float targetX, float targetY, float mapW, float mapH);