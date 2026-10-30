#include "decode.h"

void decode(Chip8 *device, uint16_t opcode){
    uint8_t index = (opcode >> 8) & 0x0F;
    uint8_t indices = (opcode >> 4);

    switch (opcode >> 12){
    case 0x0:
        switch(opcode & 0x00FF){
            case 0xE0:
                CLS(device);
                break;

            case 0xEE:
                RET(device);
                break;
        }

        break;

    case 0x1:
        JP(device, opcode & 0x0FFF);
        break;
    
    case 0x2:
        CALL(device, opcode & 0x0FFF);
        break;
    
    case 0x3:        
        SE(device, device->registers[index], opcode & 0x00FF);
        break;
    
    case 0x4:        
        SNE(device, device->registers[index], opcode & 0x00FF);
        break;

    case 0x5:
        SE(device, device->registers[indices >> 4], device->registers[indices & 0x0F]);
        break;
    
    case 0x6:        
        LD(device->registers + index, opcode);
        break;

    case 0x7:
        ADDval(device, index, opcode);
        break;

    case 0x8:
        switch(opcode & 0x000F){
            case 0x0:
                LD(device->registers + (indices >> 4), device->registers[indices & 0x0F]);
                break;

            case 0x1:
                OR(device, indices);
                break;
            
            case 0x2:

                AND(device, indices);
                break;

            case 0x3:
                XOR(device, indices);
                break;

            case 0x4:
                ADDval(device, indices >> 4, device->registers[indices & 0x0F]);
                break;
            
            case 0x5:
                SUB(device, indices);
                break;
            
            case 0x6:
                SHR(device, indices);
                break;
            
            case 0x7:
                SUBN(device, indices);
                break;
            
            case 0xE:
                SHL(device, indices);
                break;
            
            default:
                break;
        }
        break;
    
    case 0x9:
        SNE(device, device->registers[indices >> 4], device->registers[indices & 0x0F]);
        break;
    
    case 0xA:
        LDI(device, opcode & 0x0FFF);
        break;
    
    case 0xB:
        JPV0(device, opcode & 0x0FFF);
        break;
    
    case 0xC:
        RND(device, opcode >> 8, opcode);
        break;

    case 0xD:
        DRW(device, opcode >> 4, opcode);
        break;
    
    case 0xE:
        switch(opcode & 0x00FF){
            case 0xA1:
                SKNP(device, opcode >> 8);
                break;

            case 0x9E:
                SKP(device, opcode >> 8);
                break;

            default:
                break;
        }

        break;

    case 0xF:
        switch(opcode & 0x00FF){
            case 0x07:        
                LD(device->registers + index, device->delayTimer);
                break;

            case 0x0A:
                LDK(device, opcode >> 8);
                break;
            
            case 0x15:        
                LD(&device->delayTimer, device->registers[index]);
                break;

            case 0x18:        
                LD(&device->soundTimer, device->registers[index]);
                break;
            
            case 0x1E:
                ADDI(device, device->registers[index]);
                break;

            case 0x29:
                LDI(device, FONT_ADDRESS + (5 * device->registers[index]));
                break;
            
            case 0x33:
                uint8_t value = device->registers[index];
                // Get digits : Ex 255 -> 255/100 = 2, (255/10)%10 = 5, 255%10 = 5
                uint8_t digits[3] = {(value/100), (value/10)%10, value%10};

                LDinMemory(device, digits, 3);
                break;

            case 0x55:
                LDinMemory(device, device->registers, device->registers[index]+1); // Add one because register[x] is included in copy, so size is x+1
                break;

            case 0x65:
                LDinRegister(device, device->registers[index]);
                break;

            default:
                break;
        }

        break;

    default:
        break;
    }
}