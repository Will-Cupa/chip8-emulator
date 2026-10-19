#pragma once
#include <stdio.h>
#include <stdint.h>

#define MEMORY_SIZE 4096
#define ROM_ADDRESS 0x200

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
    uint32_t videoBuffer[64];
} Chip8;

int loadROM(uint8_t* buffer, FILE* rom);