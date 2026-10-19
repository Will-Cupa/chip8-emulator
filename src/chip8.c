#include "chip8.h"

int loadROM( uint8_t* buffer, FILE* rom){
    // Get rom size
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