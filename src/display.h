#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define SCALE_FAC 10
#define VBUFFER_LAST_BIT_MASK 0x8000000000000000

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Display;

Display initDisplay();

void draw(SDL_Renderer* renderer, uint64_t* videoBuffer);

void destroy(Display* display);