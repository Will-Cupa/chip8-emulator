#include "display.h"

Display initDisplay(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("%s",SDL_GetError());
        exit -1;
    }

    SDL_Window* window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SCALE_FAC, SCREEN_HEIGHT * SCALE_FAC, SDL_WINDOW_SHOWN);
    
    if(!window){
        printf("%s",SDL_GetError());
        exit -1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer){
        printf("%s",SDL_GetError());
        exit -1;
    }

    return (Display){window, renderer};
}

void draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer); //Not really clearing, more like filling

    SDL_RenderPresent(renderer);
}

void destroy(Display* display){
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}