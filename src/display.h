#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_HEIGHT 32
#define SCREEN_WIDTH 64
#define SCALE_FAC 10

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Display;

Display initDisplay();

void draw(SDL_Renderer* renderer);

void destroy(Display* display);