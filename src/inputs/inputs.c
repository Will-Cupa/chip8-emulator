#include "inputs.h"

int keymap[16] = 
{
    SDL_SCANCODE_X,
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_W,
    SDL_SCANCODE_E,
    SDL_SCANCODE_A,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_Z,
    SDL_SCANCODE_C,
    SDL_SCANCODE_4,
    SDL_SCANCODE_R,
    SDL_SCANCODE_F,
    SDL_SCANCODE_V
};

void fetchInput(uint16_t *keypad, int *runFlag){
    const uint8_t* keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        *runFlag = !(event.type == SDL_QUIT);

        for(int i=0; i<16; i++){ 
            *keypad = (*keypad & ~(1 << i)) | (keyState[keymap[i]] << i);
        }
    }
}