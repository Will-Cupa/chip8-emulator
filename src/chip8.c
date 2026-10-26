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

void skip(Chip8* device){
    device->programCounter += 2; // increment by 2 because an instruction is 2 bytes
}

// ------------- INSTRUCTION SET -------------

void CLS(Chip8* device){
    memset(device->videoBuffer, 0, VBUFFER_SIZE * sizeof(uint64_t));
}

void DRW(Chip8* device, uint8_t indices, uint8_t height){
    uint8_t x = device->registers[indices >> 4];
    uint8_t y = device->registers[indices & 0x0F];
    
    int shift = (sizeof(uint64_t) - sizeof(uint8_t)) * BYTE_SIZE - x;

    for(int i=0; i<height; i++){
        printf("video mem: %02X\n\n", device->memory[device->index + i]);
        device->videoBuffer[(y + i)] ^= ((uint64_t)device->memory[device->index + i]) << shift;
    }
}

void RET(Chip8* device){
    device->stackPointer--;
    
    JP(device, device->stack[device->stackPointer]);
}

void JP(Chip8* device, uint16_t addr){
    device->programCounter = addr;
}

void JPV0(Chip8* device, uint16_t addr){
    JP(device, addr + device->registers[0]);
}

void CALL(Chip8* device, uint16_t addr){
    device->stack[device->stackPointer] = device->programCounter;
    device->stackPointer++;
    
    JP(device, addr);
}

void SE(Chip8* device, uint8_t x, uint8_t y){
    if(x == y){
        skip(device);
    }
}

void SNE(Chip8* device, uint8_t x, uint8_t y){
    if(x != y){
        skip(device);
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

void SUB(Chip8* device, uint8_t indices){
    device->registers[0x0F] = (device->registers[indices >> 4] >= device->registers[indices & 0x0F]);
    device->registers[indices >> 4] = device->registers[indices >> 4] - device->registers[indices & 0x0F];
}

void SUBN(Chip8* device, uint8_t indices){
    device->registers[0x0F] = (device->registers[indices >> 4] <= device->registers[indices & 0x0F]);
    device->registers[indices >> 4] = device->registers[indices & 0x0F] - device->registers[indices >> 4];
}

void OR(Chip8* device, uint8_t indices){
    device->registers[indices >> 4] = device->registers[indices >> 4] | device->registers[indices & 0x0F];
}

void XOR(Chip8* device, uint8_t indices){
    device->registers[indices >> 4] = device->registers[indices >> 4] ^ device->registers[indices & 0x0F];
}

void AND(Chip8* device, uint8_t indices){
    device->registers[indices >> 4] = device->registers[indices >> 4] & device->registers[indices & 0x0F];
}

void SHR(Chip8* device, uint8_t indices){
    device->registers[0x0F] = device->registers[indices & 0x0F] & 0x01;
    device->registers[indices >> 4] = device->registers[indices & 0x0F] >> 1;
}

void SHL(Chip8* device, uint8_t indices){
    device->registers[0x0F] = device->registers[indices & 0x0F] >> 7;
    device->registers[indices >> 4] = device->registers[indices & 0x0F] << 1;
}

void RND(Chip8* device, uint8_t index, uint16_t mask){
    device->registers[index & 0x0F] = genRandom() & mask;
}

void SKP(Chip8* device, uint8_t index){
    uint8_t key = device->registers[index & 0x0F];
    
    if(device->keypad[key]){
        skip(device);
    }
}

void SKNP(Chip8* device, uint8_t index){
    uint8_t key = device->registers[index & 0x0F];
    
    if(!device->keypad[key]){
        skip(device);
    }
}