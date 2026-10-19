#include <stdio.h>
#include "chip8.h"

int main(){
    Chip8 device;

    FILE *rom = fopen("./rom/test", "r");

    if(!rom){
        printf("Could not open ROM\n");
        return 1;
    }

    if(!loadROM(device.memory, rom)){
        printf("Error while reading\n");
    }

    fclose(rom);
    
    return 0;
}