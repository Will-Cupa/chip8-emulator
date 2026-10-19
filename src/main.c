#include <stdio.h>
#include "chip8.h"

int main(){
    Chip8 device;

    FILE *rom = fopen("./rom/test", "r");

    printf("%s\n", device.memory+ROM_ADDRESS);

    if(loadROM(device.memory, rom)){
        printf("%s\n", device.memory+ROM_ADDRESS);
    }else{
        printf("Error while reading\n");
    }

    fclose(rom);
    
    return 0;
}