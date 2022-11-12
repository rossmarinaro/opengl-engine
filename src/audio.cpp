#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include "../headers/audio.h"
#include "../headers/logs.h"
//#include "../main.h"



/******************** GENERATE SINE *************/

    void Audio::sine_wave(Audio::BitDepth buffer[], double freq)
    { 
        Audio::BitDepth amplitude = std::numeric_limits<Audio::BitDepth>::max() * 0.5;
        QWORD c = 0;
        double d = (Audio::samplerate / freq);
        for (QWORD i = 0; i < Audio::NUM_SAMPLES; i += 2)
        {
            double deg = 360.0 / d;
            buffer[i] = buffer[i + (1 * (2 - 1))] = sin((c++ *deg) * Audio::pi / 180) * amplitude;
        }
    }
    template<typename _Ty> void write(std::ofstream& stream, const _Ty& ty) 
    {
	    stream.write((const char*) &ty, sizeof(_Ty));
    }

/************ WRITE FILE *********************/

    void Audio::write_file(const char* filename)
    {
        SetConsoleTitleA("PCM Audio Example");
        Audio::BitDepth* buffer = new BitDepth[Audio::NUM_SAMPLES];
        memset(buffer, 0, Audio::NUM_SAMPLES * sizeof(BitDepth));
        sine_wave(buffer, 440.0);
        std::ofstream stream(filename + std::string(".ogg"/* ".wav */), std::ios::binary);
        stream.write("RIFF", 4);
        ::write<int>(stream, 36 + (Audio::NUM_SAMPLES * sizeof(Audio::BitDepth)));
        stream.write("WAVEfmt ", 8);
        ::write<int>(stream, 16);
        ::write<short>(stream, 1);
        ::write<unsigned short>(stream, 2);
        ::write<int>(stream, Audio::samplerate);
        ::write<int>(stream, Audio::samplerate * 2 * sizeof(Audio::BitDepth));
        ::write<short>(stream, 2 * sizeof(Audio::BitDepth));
        ::write<short>(stream, sizeof(Audio::BitDepth) * 8);
        stream.write("data", 4);
        ::write<int>(stream, Audio::NUM_SAMPLES * sizeof(Audio::BitDepth));
        stream.write((const char*) &buffer[0], Audio::NUM_SAMPLES * sizeof(Audio::BitDepth));
        stream.close();
        delete[] buffer;
        Log::write(".wav written!"); 
    }

/************** LOAD AUDIO *****************/

    Mix_Chunk* Audio::load_audio(const char* filePath)
    {
		Mix_Chunk* sine = Mix_LoadWAV(filePath);
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) Log::error(SDL_GetError());
        else{
            Log::write("audio loaded");
            //Audio::play_sound(sine);
        }
        return sine;
    }
    
/************** PLAY SOUND *****************/

    void Audio::play_sound(Mix_Chunk* soundName)
    {
       // if (!load_audio("sine.wav")) Log::error(SDL_GetError());
       // else{
           // if (soundName == "sine")
            //{
                //case "sine" :
                    Mix_PlayChannel(-1, soundName, 0);
                    Log::write("played");
                    //Free resources and close SDL
                   // Mix_FreeChunk(sine);
                   // Mix_CloseAudio();Log::error(soundName);
                //break;
            //}else Log::write("idk");
        //}
    }




// ///////////// GET SFX
//     Mix_Chunk* Audio::get_SFX(std::string filepath)
//     {
//         std::string fullpath = SDL_GetBasePath();
//         fullpath.append("assets/audio" + filepath);
//         if (mSFX[fullpath] == nullptr)
//         {
//             mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());
//             if (mSFX[fullpath] == NULL) Log::error(SDL_GetError());
//         }
//         return mSFX[fullpath];
//     }
// /////////// PLAY SFX
//     void Audio::play_SFX(Mix_Chunk* filename, int loops, int channel)
//     {
//         Mix_PlayChannel(channel, filename, loops);
//     }

//////////////////////////////////////////////////////////////////////////////////

    Audio* Audio::sInstance = NULL;
    Audio* Audio::Instance()
    {
        if (sInstance == NULL) sInstance = new Audio();
        return sInstance;
    }
    
/******** CONSTRUCTOR / DESTRUCTOR ****/
    Audio::Audio()
    {
        //Audio* mAudioMgr ;//= new Audio();//Audio::Instance();
        if(SDL_Init(SDL_INIT_AUDIO) < 0) Log::error(SDL_GetError());
        else
        {
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) Log::error(SDL_GetError());
            else{
                Mix_Init(MIX_INIT_OGG);
                // Audio* audio;
                Audio::BitDepth* buffer = new Audio::BitDepth[Audio::NUM_SAMPLES];
                // Audio::write_file("sine");
                // audio->play_sound(load_audio("sine.wav")); 
                Log::write("audio initialized");
            }
        }
    }
    Audio::~Audio()
    {
        Audio* mAudioMgr = NULL;
        Mix_CloseAudio();
        Log::write("audio closed");
    }