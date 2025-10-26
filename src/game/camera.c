#include "camera.h"
#include <stdio.h>
#include <math.h>

void Camera_Init(Camera* cam, float width, float height) {
    printf("Initializing camera...\n");
    cam->x = 0.0f;
    cam->y = 0.0f;
    cam->width = width;
    cam->height = height;
    cam->targetX = 0;
    cam->targetY = 0;
    cam->smoothSpeed = 6.0f;
    cam->offsetX = 0;
    cam->offsetY = 0;
    printf("Camera initialization done.\n");
}

void Camera_Update(Camera* cam, float targetX, float targetY, float mapW, float mapH) {
    // center camera on player
    float targetCamX = targetX + cam->offsetX - cam->width / 2.0f;
    float targetCamY = targetY + cam->offsetY - cam->height / 2.0f;

    // smooth follow (10% per frame)
    cam-> x += (targetCamX - cam->x) * (cam->smoothSpeed * 0.016f);
    cam-> y += (targetCamY - cam->y) * (cam->smoothSpeed * 0.016f);

    // ------ Safe Clamping ------
    float maxX = mapW - cam->width;
    float maxY = mapH - cam->height;

    // horizontal
    if (mapW > cam->width) {
        if (cam->x < 0) cam->x = 0;
        if (cam->x > maxX) cam->x = maxX;
    } else {
        cam->x = (mapW - cam->width) / 2.0f; // center smaller maps
    }

    // vertical
    if (mapH > cam->height) {
        if (cam->y < 0) cam->y = 0;
        if (cam->y > maxY) cam->y = maxY;
    } else {
        cam->y = (mapH - cam->height) / 2.0f;
    }
}