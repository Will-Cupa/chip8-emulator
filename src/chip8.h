#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define ROM_ADDRESS 0x200

#define FONT_ADDRESS 0x050
#define FONTSET_SIZE 80
#define VBUFFER_SIZE 64

typedef struct {
    uint8_t registers[16];
    uint8_t memory[MEMORY_SIZE];
    uint16_t index;
    uint16_t programCounter;
    uint16_t stack[16];
    uint8_t stackPointer;
    uint8_t delayTimer;
    uint8_t soundTimer;
    uint8_t keypad[16];
    uint32_t videoBuffer[VBUFFER_SIZE];
} Chip8;

int loadROM(uint8_t* buffer, FILE* rom);

void loadFont(uint8_t* buffer, uint8_t* fontset);

// This function expect rand to have been initialized with srand() before
uint8_t genRandom();

// ------------- INSTRUCTION SET -------------

void CLS(Chip8* device);

void RET(Chip8* device);

void JP(Chip8* device, uint16_t addr);

void CALL(Chip8* device, uint16_t addr);

void SE(Chip8* device, uint8_t x, uint8_t y);

void SNE(Chip8* device, uint8_t x, uint8_t y);

void ADDval(Chip8* device, uint8_t index, uint8_t val);

void ADDI(Chip8* device, uint8_t val);

// One index is half a byte, so we pass two of them as one byte
void ADDregister(Chip8* device, uint8_t indices);

void OR(Chip8* device, uint8_t indices);