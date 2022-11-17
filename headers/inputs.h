#pragma once

#include "./logs.h"
#include "./renderer.h"


class Inputs {

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

        static void processInput(GLFWwindow *window)
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (action == GLFW_PRESS)
            {
                switch (key)
                {
                    case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GLFW_TRUE); break;
                    case GLFW_KEY_LEFT: Inputs::m_left = true; break;
                    case GLFW_KEY_RIGHT:Inputs:: m_right = true; break; 
                    case GLFW_KEY_UP: Inputs::m_down = true; break;
                    case GLFW_KEY_DOWN: Inputs::m_up = true; break;

                    case GLFW_KEY_W: break;
                    default: break;
                }
            }
            else
            {
                Inputs::m_left = false; 
                Inputs::m_right = false; 
                Inputs::m_up = false;
                Inputs::m_down = false;
            }
        }

        ~Inputs(){ }
};


 
    
 

