#include "core/engine.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main(void)
{
    Engine engine;
    if(!Engine_Init(&engine, "game", 800, 600)) {
        return 1;
    }

    SDL_Texture* tex = IMG_LoadTexture(engine.renderer, "assets/Banana.png");

    while (engine.running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT){
                engine.running = false;
            }
        }

        Engine_BeginFrame(&engine);

        SDL_FRect rect = { 384, 284, 32, 32 };
        SDL_RenderTexture(engine.renderer, tex, NULL, &rect);

        Engine_EndFrame(&engine);
    }

    Engine_Quit(&engine);
    return 0;
}
