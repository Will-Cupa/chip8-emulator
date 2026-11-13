#include "sound.h"

SoundDevice initSoundDevice(){
    // opening an audio device:
    SDL_AudioSpec audio_spec;
    SDL_zero(audio_spec);
    audio_spec.freq = 44100;
    audio_spec.format = AUDIO_S16SYS;
    audio_spec.channels = 1;
    audio_spec.samples = 1024;
    audio_spec.callback = NULL;

    // the representation of our audio device in SDL
    SDL_AudioDeviceID audio_device = SDL_OpenAudioDevice(NULL, 0, &audio_spec, NULL, 0);

    uint32_t sample_bytes = audio_spec.freq * sizeof(int16_t);
    int16_t* samples = malloc(sample_bytes);

    float x = 0.0f;
    for (int i = 0; i < audio_spec.freq; i++) {
        samples[i] = sin(x * 4) * 5000;
        x += .010f;
    }

    // SDL_QueueAudio(audio_device, samples, sample_bytes);

    return (SoundDevice){audio_device, samples, sample_bytes, 0};
}


void play(SoundDevice *soundDevice){
    SDL_QueueAudio(soundDevice->SDL_audioDevice, soundDevice->audioSample, soundDevice->audioSize);
    SDL_PauseAudioDevice(soundDevice->SDL_audioDevice, 0);
    soundDevice->isPlaying=1;
}


void stop(SoundDevice *soundDevice){
    if(soundDevice->isPlaying){
        SDL_PauseAudioDevice(soundDevice->SDL_audioDevice, 1);
        soundDevice->isPlaying=0;
    }

}


void destroySoundDevice(SoundDevice *soundDevice){
    free(soundDevice->audioSample);
    SDL_CloseAudioDevice(soundDevice->SDL_audioDevice);
}