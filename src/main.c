#include <stdio.h>
#include <time.h>
#include "decode.h"
#include "display.h"

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

int keymap[16] = 
{
    SDL_SCANCODE_X,
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_Q,
    SDL_SCANCODE_W,
    SDL_SCANCODE_E,
    SDL_SCANCODE_A,
    SDL_SCANCODE_S,
    SDL_SCANCODE_D,
    SDL_SCANCODE_Z,
    SDL_SCANCODE_C,
    SDL_SCANCODE_4,
    SDL_SCANCODE_R,
    SDL_SCANCODE_F,
    SDL_SCANCODE_V
};

int main(){
    Chip8 device;

    // Open the rom file
    FILE *rom = fopen("./rom/Keypad_Test_fixed.ch8", "r");

    if(!rom){
        printf("Could not open ROM\n");
        return 1;
    }

    // Load rom into memory
    if(!loadROM(device.memory, rom)){
        printf("Error while reading\n");
    }

    // Close rom file
    fclose(rom);

    // Load fontset into memory
    loadFont(device.memory, fontset);

    // Initialize random with current time as seed
    srand(time(NULL));

    // Initialize graphic library
    Display display = initDisplay();

    // Set program counter to beginning of rom 
    device.programCounter = ROM_ADDRESS;
    // Set stack pointer to 0
    device.stackPointer = 0;

    // Clear keypad state
    device.keypad = 0; 
    // Clear display
    CLS(&device);

    SDL_Event event;
    const uint8_t* keyState = SDL_GetKeyboardState(NULL);
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            if (event.type == SDL_KEYDOWN){
                printf("scancode: %d\n", event.key.keysym.scancode);
            }
        }
        
        // printf("SCANCODE_2: %d\n", keyState[SDL_SCANCODE_2]);
        
        for(int i=0; i<16; i++){
            if(keyState[keymap[i]]){
                device.keypad |= (1 << i);
                // printf("keypad %016b\n", device.keypad);
            }
        }

        // opcode is stored in two cell of memory because one opcode is 16bit
        // uint16_t opcode = (device.memory[device.programCounter] << 8) | device.memory[device.programCounter+1];
        // // printf("%04x\n", opcode);

        // // Increment program counter
        // skip(&device);

        // decode(&device, opcode);

        // draw(display.renderer, device.videoBuffer);
    }


    destroy(&display);
    return 0;
}