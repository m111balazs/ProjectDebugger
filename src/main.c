#include "core/engine.h"
#include "core/input.h"
#include "graphics/texture.h"
#include "graphics/animation.h"
#include "game/tilemap.h"
#include "game/collision.h"
#include <SDL3/SDL.h>
#include <stdio.h>

#define TILE_SIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 18

int windowWidth = MAP_WIDTH * TILE_SIZE + 64;
int windowHeight = MAP_HEIGHT * TILE_SIZE + 64;

int mapData[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,3,0,0,0,0,1},
    {1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,0,0,0,0,0,0,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int* mapPtr = &mapData[0][0];

const char* tileset[] = {
    "assets/Grass.png", // 0
    "assets/Wall.png", // 1
    "assets/Water.png", // 2
    "assets/Stone.png" // 3
};

int main(void){
    Engine engine;
    printf("Engine init starting...\n");

    if(!Engine_Init(&engine, "Project Debugger", windowWidth, windowHeight)){
        printf("Engine init failed...\n");
        return 1;
    }

    printf("Engine done.\n");

    // --- SYSTEM INITIALIZATION ---
    TextureManager_Init(engine.renderer);

    Tilemap tilemap;
    if (!Tilemap_Load(&tilemap, engine.renderer, tileset, 4, mapPtr, MAP_WIDTH, MAP_HEIGHT, 32)){
        printf("Tilemap failed to load\n");
    } else printf("Tilemap loaded!\n");

    Animation walkAnim;
    if (!Animation_Load(&walkAnim, engine.renderer, "assets/Player_Walk.png", 32, 32, 4, 8)) {
        printf("Animation failed to load!\n");
    } printf("Animation loaded!\n");

    SDL_Texture* player = Texture_Load("assets/Player.png");

    float playerX = 384.0f, playerY = 284.0f;
    float speed = 200.0f;
    float spriteW = 32.0f;
    float spriteH = 32.0f;
    bool moving = false;

    SDL_Event e;
    printf("Entering main loop...\n");

    while (engine.running)
    {
        Input_BeginFrame();

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT){
                engine.running = false;
            }
            Input_ProcessEvent(&e);
        }

        // --- MOVEMENT LOGIC ---
        moving = false;
        float moveX = 0.0f, moveY = 0.0f;

        if (Input_IsKeyDown(SDLK_W)) { moveY -= 1; moving = true; }
        if (Input_IsKeyDown(SDLK_S)) { moveY += 1; moving = true; }
        if (Input_IsKeyDown(SDLK_A)) { moveX -= 1; moving = true; }
        if (Input_IsKeyDown(SDLK_D)) { moveX += 1; moving = true; }

        float len = SDL_sqrtf(moveX * moveX + moveY * moveY);
        if (len > 0) {
            moveX /= len;
            moveY /= len;
        }

        playerX += moveX * speed * engine.deltaTime;
        playerY += moveY * speed * engine.deltaTime;
        
        float proposedX = playerX + moveX * speed * engine.deltaTime;
        float proposedY = playerY + moveY * speed * engine.deltaTime;

        // Collision check for X
        if (!Collision_Check(proposedX, playerY, spriteW, spriteH, &tilemap))
        playerX = proposedX;

        // Collision check for Y
        if (!Collision_Check(playerX, proposedY, spriteW, spriteH, &tilemap))
        playerY = proposedY;

        if (moving) {
            Animation_Update(&walkAnim, engine.deltaTime);
        }

        // --- RENDER ---
        Engine_BeginFrame(&engine);
        Tilemap_Render(&tilemap, engine.renderer);
        Animation_Render(&walkAnim, engine.renderer, playerX, playerY);
        Engine_EndFrame(&engine);

        Input_EndFrame();
    }

    printf("Main loop finished\n");
    Animation_Destroy(&walkAnim);
    Tilemap_Destroy(&tilemap);
    Engine_Quit(&engine);

    printf("Done\n");
    return 0;
}