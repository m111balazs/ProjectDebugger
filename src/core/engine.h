#pragma once
#include <SDL3/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    float deltaTime;
    Uint64 lastFrame;
} Engine;

bool Engine_Init(Engine* engine, const char* title, int width, int height);
void Engine_Quit(Engine* engine);
void Engine_BeginFrame(Engine* engine);
void Engine_EndFrame(Engine* engine);