#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

void Input_BeginFrame(void);
void Input_ProcessEvent(SDL_Event* e);
void Input_EndFrame(void);

bool Input_IsKeyDown(SDL_Keycode key);
bool Input_IsKeyPressed(SDL_Keycode key);
bool Input_IsKeyReleased(SDL_Keycode key);
