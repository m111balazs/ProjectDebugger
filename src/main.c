#include "core/engine.h"
#include "core/input.h"
#include "graphics/texture.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int main(void)
{
    int windowWidth = 800;
    int windowHeight = 600;

    Engine engine;
    if(!Engine_Init(&engine, "game", windowWidth, windowHeight)) {
        return 1;
    }

    TextureManager_Init(engine.renderer);
    SDL_Texture* player = Texture_Load("assets/Player.png");
    SDL_Texture* grass = Texture_Load("assets/Grass.png");

    float playerX = 384, playerY = 284;
    float speed = 200.0f;
    float spriteW = 32;
    float spriteH = 32;

    SDL_Event e;

    while (engine.running) {
        Input_BeginFrame();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT){
                engine.running = false;
            }

            Input_ProcessEvent(&e);
        }

        // ---- MOVEMENT LOGIC ----
        float moveX = 0.0f;
        float moveY = 0.0f;

        if (Input_IsKeyDown(SDLK_W)) moveY = -1;
        if (Input_IsKeyDown(SDLK_S)) moveY =  1;
        if (Input_IsKeyDown(SDLK_A)) moveX = -1;
        if (Input_IsKeyDown(SDLK_D)) moveX =  1;

        float len = SDL_sqrtf(moveX * moveX + moveY * moveY);
        if (len > 0) {
            moveX /= len;
            moveY /= len;
        }

        playerX += moveX * speed * engine.deltaTime;
        playerY += moveY * speed * engine.deltaTime;

        // ---- BOUNDARY LIMITS ----
        if (playerX < 0) playerX = 0;
        if (playerY < 0) playerY = 0;
        if (playerX > 800 - 32) playerX = 800 - 32;
        if (playerY > 600 - 32) playerY = 600 - 32;

        Engine_BeginFrame(&engine);

        SDL_FRect dest = { playerX, playerY, 32, 32 };
        SDL_RenderTexture(engine.renderer, player, NULL, &dest);

        Engine_EndFrame(&engine);
        Input_EndFrame();
    }

    TextureManager_Quit();
    Engine_Quit(&engine);
    return 0;
}
