#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

#include "./logs.h"
//#include "./audio.h"

class Inputs{

    private:

        static int gKeyPressSurfaces[];
        static bool success;
        static Inputs* sInstance;
        Inputs* mInputs;                 

    public:

        bool m_left;
        bool m_right;
        bool m_up;
        bool m_down;

        enum keyPressSurfaces {
            KEY_PRESS_SURFACE_DEFAULT,
            KEY_PRESS_SURFACE_UP,
            KEY_PRESS_SURFACE_DOWN,
            KEY_PRESS_SURFACE_LEFT,
            KEY_PRESS_SURFACE_RIGHT,
            KEY_PRESS_SURFACE_TOTAL
        };

        bool pollInput(SDL_Event &event, GLFWwindow* window)
        {
        
        //on quit
        
            if (
                event.type == SDL_QUIT || 
                event.type == SDL_WINDOWEVENT && 
                event.window.event == SDL_WINDOWEVENT_CLOSE && 
                event.window.windowID == glfwGetWindowAttrib(window, 0) 
            )
                return false;

        //on key down

            if(event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                 //   case SDLK_1 : Audio::play_sound(Audio::load_audio("sine.wav")); break;
                    case SDLK_2 : system("gnome-terminal -x 'sh -c \"g++ y.cpp && ./a.out\"'"); break;
                    case SDLK_LEFT: m_left = true; break;
                    case SDLK_RIGHT: m_right = true; break; 
                    case SDLK_UP: m_up = true; break;
                    case SDLK_DOWN: m_down = true; break;
                    case SDLK_3 : 
                        return false; 
                    default: 
                        Log::error(Mix_GetError());
                    break; 
                }
            }
            else
            {
                m_left = false; 
                m_right = false; 
                m_up = false;
                m_down = false;
            }

            return true;
            
        }

    ~Inputs()
    {
        //Deallocate surfaces
        // for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
        // {
        // 	SDL_FreeSurface( gKeyPressSurfaces[ i ] );
        // 	gKeyPressSurfaces[ i ] = NULL;
        // }
    }
};
    
//#endif 



