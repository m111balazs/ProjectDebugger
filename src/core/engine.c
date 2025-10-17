#include <engine.h>
#include <stdio.h>

bool Engine_Init(Engine* engine, const char* title, int width, int height){
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL init error: %s\n", SDL_GetError());
        return false;
    }

    engine->window = SDL_CreateWindow(title, width, height, 0);
    engine->renderer = SDL_CreateRenderer(engine->window, NULL);

    engine->running = true;
    engine->lastFrame = SDL_GetTicks();
    return true;
}

void Engine_BeginFrame(Engine* engine) {
    Uint64 now = SDL_GetTicks();
    engine->deltaTime = (now - engine->lastFrame) / 1000.0f;
    engine->lastFrame = now;

    SDL_SetRenderDrawColor(engine->renderer, 40, 120, 200, 255);
    SDL_RenderClear(engine->renderer);
}

void Engine_EndFrame(Engine* engine) {
    SDL_RenderPresent(engine->renderer);
}

void Engine_Quit(Engine* engine) {
    SDL_DestroyRenderer(engine->renderer);
    SDL_DestroyWindow(engine->window);
    SDL_Quit();
}