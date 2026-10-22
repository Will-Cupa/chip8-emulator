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
    
    JP(device, device->stack[device->stackPointer]);
}

void JP(Chip8* device, uint16_t addr){
    device->programCounter = addr;
}

void CALL(Chip8* device, uint16_t addr){
    device->stack[device->stackPointer] = device->programCounter;
    device->stackPointer++;
    
    JP(device, addr);
}

void SE(Chip8* device, uint8_t x, uint8_t y){
    if(x == y){
        device->programCounter += 2; // increment by 2 because an instruction is 2 bytes
    }
}

void SNE(Chip8* device, uint8_t x, uint8_t y){
    if(x != y){
        device->programCounter += 2;
    }
}

void ADDval(Chip8* device, uint8_t index, uint8_t val){
    device->registers[index & 0x0F] = (device->registers[index & 0x0F] + val)%256;
}

void ADDI(Chip8* device, uint8_t val){
    device->index += val;
}

void ADDregister(Chip8* device, uint8_t indices){
    uint16_t result = (device->registers[indices >> 4] + device->registers[indices & 0x0F])%256;

    device->registers[indices >> 4] = result;
    device->registers[0x0F] = (result > 255);
}

void OR(Chip8* device, uint8_t indices){
    device->registers[indices >> 4] = device->registers[indices >> 4] | device->registers[indices & 0x0F];
}
