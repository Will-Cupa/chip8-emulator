#include "display.h"

Display initDisplay(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("%s",SDL_GetError());
        exit -1;
    }

    // SDL2 bug with linux, on some keyboards, text input prevent certain keys to produce scancode
    // See issue : https://github.com/libsdl-org/sdl/issues/14239
    SDL_StopTextInput();

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

void draw(SDL_Renderer* renderer, uint64_t* videoBuffer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); //Not really clearing, more like filling

    uint64_t currentLine;
    SDL_Rect *rect = malloc(sizeof(SDL_Rect));

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for(int i=0; i < SCREEN_HEIGHT; i++){
        currentLine = videoBuffer[i];
        
        for(int j=0; j < SCREEN_WIDTH; j++){
            if(currentLine & VBUFFER_LAST_BIT_MASK){
                // printf("draw at %d, %d\n", j, i);

                *rect = (SDL_Rect){j*SCALE_FAC, i*SCALE_FAC, SCALE_FAC, SCALE_FAC};

                SDL_RenderFillRect(renderer, rect);
            }

            currentLine <<= 1;
        }
    }

    free(rect);

    SDL_RenderPresent(renderer);
}

void destroyDisplay(Display* display){
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}