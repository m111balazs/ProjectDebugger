#include "camera.h"
#include <stdio.h>
#include <math.h>

void Camera_Init(Camera* cam, float width, float height) {
    printf("Initializing camera...\n");
    cam->x = 0.0f;
    cam->y = 0.0f;
    cam->width = width;
    cam->height = height;
    printf("Camera initialization done.\n");
}

void Camera_Update(Camera* cam, float targetX, float targetY, float mapW, float mapH) {
    // center camera on player
    float targetCamX = targetX - cam->width / 2.0f;
    float targetCamY = targetY - cam->height / 2.0f;

    // smooth follow (10% per frame)
    cam-> x += (targetCamX - cam->x) * 0.1f;
    cam-> y += (targetCamY - cam->y) * 0.1f;

    // ------ Safe Clamping ------
    // horizontal
    if (mapW > cam->width) {
        if (cam->x < 0) cam->x = 0;
        if (cam->x + cam->width >= mapW)
            cam->x = mapW - cam->width - 1.0f;
    } else {
        cam->x = (mapW - cam->width) / 2.0f; // center smaller maps
    }

    // vertical
    if (mapH > cam->height) {
        if (cam->y < 0) cam->y = 0;
        if (cam->y + cam->height >= mapH)
            cam->y = mapH - cam->height - 1.0f;
    } else {
        cam->y = (mapH - cam->height) / 2.0f; // center smaller maps
    }

    // --- fail-safe against NaN or overflow ---
    if (cam->x != cam->x || cam->y != cam->y) {
        cam->x = 0;
        cam->y = 0;
    }
}