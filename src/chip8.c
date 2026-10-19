#include "chip8.h"

int loadROM( uint8_t* buffer, FILE* rom){
    // go at the end
    fseek(rom, 0, SEEK_END);
    // ask for position (equivalent to file size)
    long size = ftell(rom);
    printf("%ld \n", size);

    // Reset cursor
    fseek(rom, 0, SEEK_SET);

    if(size>=(MEMORY_SIZE-ROM_ADDRESS)){
        return 0;
    }

    // Copy in memory
    fread(buffer+ROM_ADDRESS, size, 1, rom);

    return 1;
}