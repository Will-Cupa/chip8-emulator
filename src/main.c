#include <stdio.h>
#include <time.h>
#include "decode.h"
#include "display.h"
#include "sound.h"
#include "inputManager.h"

// in hertz
#define DEFAULT_CLOCK_SPEED 400.0f

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

int main(int argc, char* argv[]){
    float clockSpeed = DEFAULT_CLOCK_SPEED;
    char* romFile = NULL;

    for(int i=1; i<argc; i++){
        if(strcmp(argv[i],"--clock-speed") == 0){
            clockSpeed = atof(argv[i+1]);
            i++; //To ignore value of current option in next iteration
        }else{
            romFile=argv[i];
        }
    }

    if(romFile == NULL){
        printf("Show help\n");
        return 0;
    }

    Chip8 device;

    // Open the rom file
    FILE *rom = fopen(romFile, "r");
    
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

    int running = 1;
    clock_t beginTime;

    SoundDevice soundDevice = initSoundDevice();

    while (running) {
        beginTime = clock();
        fetchInput(&device.keypad, &running);
        // opcode is stored in two cell of memory because one opcode is 16bit
        uint16_t opcode = (device.memory[device.programCounter] << 8) | device.memory[device.programCounter+1];
        // printf("%04x\n", opcode);

        // Increment program counter
        skip(&device);

        // Decrement delay timer
        if(device.delayTimer > 0){
            device.delayTimer--;
        }

        // Decrement sound timer and play sound
        if(device.soundTimer > 0){
            play(&soundDevice);
            device.soundTimer--;
        }else{
            stop(&soundDevice);
        }

        decode(&device, opcode);

        draw(display.renderer, device.videoBuffer);
        
        while(clockSpeed && clock() - beginTime < CLOCKS_PER_SEC/clockSpeed);
    }

    destroySoundDevice(&soundDevice);
    destroyDisplay(&display);
    return 0;
}