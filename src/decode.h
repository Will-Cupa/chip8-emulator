#pragma once
#include "chip8.h"

void decode(Chip8 *device, uint16_t opcode);

// // Switch case on different SE/SNE
// void SEhandler(Chip8* device, uint16_t opcode);

// // Switch case on different LD
// void LDhandler(Chip8* device, uint16_t opcode);

// // Split an opcode with a 16bit arg to two 8bit args and switch case on different instruction 
// void splitOpcodeHandler(Chip8* device, uint16_t opcode);

// // instruction without args (CLS and RET)
// void noArgHandler(Chip8* device, uint16_t index);

// // ----- Main opcode Table -----

// void (*masterTable[16])(Chip8*, uint16_t) = {
//     noArgHandler,
//     JP,
//     CALL,
//     SEhandler, //SE Vx byte
//     SEhandler, //SNE Vx byte
//     SEhandler, //SE Vx Vy
//     LDhandler, // LD Vx byte
//     splitOpcodeHandler, // ADD Vx, byte 
//     table8Handler,
//     SEhandler, //SNE Vx Vy
//     LDI, // LD I addr // Could be LDhandler for more unified approach
//     JPV0, // JP V0, addr
//     splitOpcodeHandler, // RND Vx, Mask // TODO set mask to 8bit
//     splitOpcodeHandler, // DRW Vx, Vy, Height
//     tableE,
//     tableF
// };

// // ----- table8 -----

// void (*table8[9])(Chip8*, uint16_t) = {
//     LDhandler, // LD Vx, Vy
//     OR,
//     AND,
//     XOR,
//     splitOpcodeHandler, // ADD Vx Vy
// };

// void table8Handler(Chip8* device, uint16_t index);