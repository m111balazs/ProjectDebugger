#include "core/engine.h"
#include "core/input.h"
#include "graphics/texture.h"
#include "graphics/animation.h"
#include "game/tilemap.h"
#include "game/collision.h"
#include "game/camera.h"
#include "game/utils.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define MAP_WIDTH 100
#define MAP_HEIGHT 100

int windowWidth = 800;
int windowHeight = 600;

int mapData[MAP_HEIGHT][MAP_WIDTH];

void GenerateTestMap() {
    srand((unsigned int)time(NULL));

    for (int y = 0; y < MAP_HEIGHT; y++){
        for (int x = 0; x < MAP_WIDTH; x++){
            if(y == 0 || x == 0 || y == MAP_HEIGHT - 1 || x == MAP_WIDTH - 1){
                mapData[y][x] = 1;
            } else {
                int r = rand() % 100;
                if(r < 5){
                    mapData[y][x] = 2; // 5% water
                } else if (r < 8){
                    mapData[y][x] = 3; // 3% stone
                } else{
                    mapData[y][x] = 0; // grass
                }
            }
        }
    }
}

const char* tileset[] = {
    "assets/Grass.png", // 0
    "assets/Wall.png", // 1
    "assets/Water.png", // 2
    "assets/Stone.png" // 3
};

Camera camera;
Camera* gCamera = &camera;

int main(void){
    Engine engine;
    printf("Engine init starting...\n");

    if(!Engine_Init(&engine, "Project Debugger", windowWidth, windowHeight)){
        printf("Engine init failed...\n");
        return 1;
    } printf("Engine done.\n");

    // --- SYSTEM INITIALIZATION ---
    TextureManager_Init(engine.renderer);

    GenerateTestMap();
    int* mapPtr = &mapData[0][0];

    Tilemap tilemap;
    if (!Tilemap_Load(&tilemap, engine.renderer, tileset, 4, mapPtr, MAP_WIDTH, MAP_HEIGHT, TILE_SIZE)){
        printf("Tilemap failed to load\n");
    } else printf("Tilemap loaded!\n");

    Animation walkAnim;
    if (!Animation_Load(&walkAnim, engine.renderer, "assets/Player_Walk.png", 32, 32, 4, 8)) {
        printf("Animation failed to load!\n");
    } printf("Animation loaded!\n");

    Camera_Init(&camera, (float)windowWidth, (float)windowHeight);
    
    SDL_Texture* player = Texture_Load("assets/Player.png");

    float playerX, playerY;
    FindRandomSpawn(&tilemap, &playerX, &playerY);
    printf("player spawned at %.1f, %.1f\n", playerX, playerY);
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

        // Axis-aligned collision resolution without pre-applying movement
        float proposedX = playerX + moveX * speed * engine.deltaTime;
        if (!Collision_Check(proposedX, playerY, spriteW, spriteH, &tilemap)) {
            playerX = proposedX;
        }

        float proposedY = playerY + moveY * speed * engine.deltaTime;
        if (!Collision_Check(playerX, proposedY, spriteW, spriteH, &tilemap)) {
            playerY = proposedY;
        }

        if (moving) {
            Animation_Update(&walkAnim, engine.deltaTime);
        }

        Camera_Update(&camera,
            playerX + spriteW / 2.0f,
            playerY + spriteH / 2.0f,
            tilemap.width * tilemap.tileSize,
            tilemap.height * tilemap.tileSize);

        // --- RENDER ---
        Engine_BeginFrame(&engine);

        Tilemap_Render(&tilemap, engine.renderer);
        Animation_Render(&walkAnim, engine.renderer, 
            playerX - camera.x, playerY - camera.y);
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

