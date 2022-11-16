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

        static bool m_left,
                    m_right,
                    m_up,
                    m_down; 

        enum keyPressSurfaces {
            KEY_PRESS_SURFACE_DEFAULT,
            KEY_PRESS_SURFACE_UP,
            KEY_PRESS_SURFACE_DOWN,
            KEY_PRESS_SURFACE_LEFT,
            KEY_PRESS_SURFACE_RIGHT,
            KEY_PRESS_SURFACE_TOTAL
        };

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (action == GLFW_PRESS)
            {
                switch (key)
                {
                    case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
                    case GLFW_KEY_LEFT: Inputs::m_left = true; break;
                    case GLFW_KEY_RIGHT:Inputs:: m_right = true; break; 
                    case GLFW_KEY_UP: Inputs::m_up = true; break;
                    case GLFW_KEY_DOWN: Inputs::m_down = true; break;

                    case GLFW_KEY_W:
                    
                        break;
                    default:
                    
                        break;
                }
            }
            else
            {
                // Inputs::m_left = false; 
                // Inputs::m_right = false; 
                // Inputs::m_up = false;
                // Inputs::m_down = false;
            }
        };


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



