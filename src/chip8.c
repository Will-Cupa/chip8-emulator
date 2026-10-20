#include "chip8.h"

int loadROM( uint8_t* buffer, FILE* rom){
    // go at the end
    fseek(rom, 0, SEEK_END);
    // ask for position (equivalent to file size)
    long size = ftell(rom);

    // Reset cursor
    fseek(rom, 0, SEEK_SET);

    if(size>=(MEMORY_SIZE-ROM_ADDRESS)){
        return 0;
    }

    // Copy in memory
    fread(buffer+ROM_ADDRESS, size, 1, rom);

    return 1;
}

void loadFont(uint8_t* buffer, uint8_t* fontset){
    for(int i=0; i < FONTSET_SIZE; i++){
        buffer[FONT_ADDRESS + i] = fontset[i];
    }
}

// This function expect rand to have been initialized with srand() before
uint8_t genRandom(){
    return rand()%255;
}

// ------------- INSTRUCTION SET -------------

void CLS(Chip8* device){
    memset(device->videoBuffer, 0, VBUFFER_SIZE * sizeof(uint32_t));
}

void RET(Chip8* device){
    device->stackPointer--;
    device->programCounter = device->stack[device->stackPointer];
}