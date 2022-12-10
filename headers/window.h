#ifndef WINDOW_H
#define WINDOW_H

#include "glm/glm.hpp"


#include "./renderer.h"
#include "./inputs.h"
#include "./logs.h"
#include "./game.h"

// #include "../vendors/imgui/imgui.h"
// #include "../vendors/imgui/imgui_impl_glfw.h"
// #include "../vendors/imgui/imgui_impl_opengl3.h"


class Window {

    public:

        static int width,
                   height;

        static GLFWwindow* m_window; 

        static int InitializeWindow();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void updateProjectionMatrix();
        
     
        Window& get()
        {
            return *this;
        }

    private:

        static Shader* m_projMatShader;

};

#endif


