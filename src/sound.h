#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>

typedef struct{
    SDL_AudioDeviceID SDL_audioDevice;
    int16_t* audioSample;
    int audioSize;
    int isPlaying;
} SoundDevice;

SoundDevice initSoundDevice();

void play(SoundDevice *soundDevice);

void stop(SoundDevice *soundDevice);

void destroySoundDevice(SoundDevice *soundDevice);