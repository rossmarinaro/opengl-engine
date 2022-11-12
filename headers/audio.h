#pragma once



/****** AUDIO *****/

#include <SDL2/SDL.h>
#include <fstream>
#include <limits>
#include <string>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <map>


class Audio {
    private:
        static Audio* sInstance;
        //Audio* mAudioMgr;
    ////maps
        std::map<std::string, Mix_Music*> mMusic;
        std::map<std::string, Mix_Chunk*> mSFX;
    public:
    
        Audio* mAudioMgr;

        typedef signed short BitDepth;
        typedef unsigned long long QWORD;
        static constexpr double pi = 3.141592653589;
        static const DWORD samplerate = 44100;
        static const WORD channels = 2;
        static const unsigned short SOUND_DURATION = 1;
        static const QWORD NUM_SAMPLES = SOUND_DURATION * samplerate * channels;

  
    //// methods
        Mix_Chunk* get_SFX(std::string filename);
        /* static */ void play_SFX(Mix_Chunk* filename, int loops = 0, int channel = 0);
        static Audio* Instance();


        static Mix_Chunk* load_audio(const char*);
        static void play_sound(Mix_Chunk* /* const char* */);
        static void sine_wave(BitDepth buffer[], double freq);
        static void write_file(const char* filename);

        Audio();
       ~Audio(); 

};

//Mix_Chunk* sine;