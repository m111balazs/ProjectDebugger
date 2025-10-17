#include "core/engine.h"
#include "core/input.h"
#include "graphics/texture.h"
#include "graphics/animation.h"
#include "game/tilemap.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

int mapData[10][10] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,2,0,0,0,3,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,3,0,0,2,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

// Convert 2D array to 1D pointer
int* mapPtr = &mapData[0][0];

// List of tile image paths (index matches map number)
const char* tileset[] = {
    "assets/Grass.png", // 0
    "assets/Wall.png",  // 1
    "assets/Water.png", // 2
    "assets/Stone.png"  // 3
};

int main(void)
{
    int windowWidth = 800;
    int windowHeight = 600;

    Engine engine;
    if(!Engine_Init(&engine, "game", windowWidth, windowHeight)) {
        return 1;
    }

    Tilemap tilemap;
    Tilemap_Load(&tilemap, engine.renderer, tileset, 4, mapPtr, 10, 10, 32);

    Animation walkAnim;
    Animation_Load(&walkAnim, engine.renderer, "assets/Player_Walk.png", 32, 32, 4, 8);

    TextureManager_Init(engine.renderer);
    SDL_Texture* player = Texture_Load("assets/Player.png");
    SDL_Texture* grass = Texture_Load("assets/Grass.png");

    float playerX = 384, playerY = 284;
    float speed = 200.0f;
    float spriteW = 32;
    float spriteH = 32;
    bool moving = false;

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
        moving = false;
        float moveX = 0.0f;
        float moveY = 0.0f;

        if (Input_IsKeyDown(SDLK_W)) { moveY = -1; moving = true; }
        if (Input_IsKeyDown(SDLK_S)) { moveY = +1; moving = true; }
        if (Input_IsKeyDown(SDLK_A)) { moveX = -1; moving = true; }
        if (Input_IsKeyDown(SDLK_D)) { moveX = +1; moving = true; }

        float len = SDL_sqrtf(moveX * moveX + moveY * moveY);
        if (len > 0) {
            moveX /= len;
            moveY /= len;
        }

        playerX += moveX * speed * engine.deltaTime;
        playerY += moveY * speed * engine.deltaTime;

        if (moving) Animation_Update(&walkAnim, engine.deltaTime);

        // ---- BOUNDARY LIMITS ----
        if (playerX < 0) playerX = 0;
        if (playerY < 0) playerY = 0;
        if (playerX > 800 - 32) playerX = 800 - 32;
        if (playerY > 600 - 32) playerY = 600 - 32;

        Engine_BeginFrame(&engine);
        Tilemap_Render(&tilemap, engine.renderer);
        Animation_Render(&walkAnim, engine.renderer, playerX, playerY);
        Engine_EndFrame(&engine);

        Input_EndFrame();
    }

    Animation_Destroy(&walkAnim);
    Tilemap_Destroy(&tilemap);
    Engine_Quit(&engine);
    return 0;
}
