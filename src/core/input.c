#include "input.h"
#include <string.h>

#define MAX_KEYS 512

static bool keysDown[MAX_KEYS];
static bool keysPressed[MAX_KEYS];
static bool keysReleased[MAX_KEYS];

static int KeyToIndex(SDL_Keycode key){
    if(key < 0 || key >= MAX_KEYS) return 0;
    return (int)key % MAX_KEYS; 
}

void Input_BeginFrame(void){
    memset(keysPressed, 0, sizeof(keysPressed));
    memset(keysReleased, 0, sizeof(keysReleased));
}

void Input_ProcessEvent(SDL_Event* e){
    if (e->type == SDL_EVENT_KEY_DOWN){
        int idx = KeyToIndex(e->key.key);
        if(!keysDown[idx])
            keysPressed[idx] = true;
        keysDown[idx] = true;
    }
    else if (e->type == SDL_EVENT_KEY_UP){
        int idx = KeyToIndex(e->key.key);
        keysDown[idx] = false;
        keysReleased[idx] = true;
    }
}

void Input_EndFrame(void){
    // could reset frame-based flags here if needed
}

bool Input_IsKeyDown(SDL_Keycode key){
    return keysDown[KeyToIndex(key)];
}

bool Input_IsKeyPressed(SDL_Keycode key){
    return keysPressed[KeyToIndex(key)];
}

bool Input_IsKeyReleased(SDL_Keycode key){
    return keysReleased[KeyToIndex(key)];
}