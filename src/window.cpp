#include "../headers/window.h"


float highDPIscaleFactor = 1.0;
bool isRunning = true,
     show_demo_window = true,
     show_another_window = false;

static const int WIDTH = 1280; 
static const int HEIGHT = 720; 

GLFWwindow* window; 


GLuint TextureID[3];
ImGuiIO io;
ImVec4 clear_color;


 
// void LaunchGui(const char* glsl_version, Inputs* inputs, SDL_Event event)
// {
//     // Load Fonts
//     // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
//     // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
//     // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
//     // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
//     // - Read 'docs/FONTS.md' for more instructions and details.
//     // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
//     // io.Fonts->AddFontDefault();
//     // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
//     // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
//     // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
//     // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
//     // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
//     // IM_ASSERT(font != NULL);



//     //     Poll and handle events (inputs, window resize, etc.)
//     //     You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
//     //     - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
//     //     - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
//     //     Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

//     IMGUI_CHECKVERSION(); 
//     ImGui::CreateContext();
//     ImGuiIO& io = ImGui::GetIO(); (void)io;
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

// //Setup Dear ImGui style

//     ImGui::StyleColorsDark();
//     ImGui::StyleColorsClassic();

// // Setup Platform/Renderer backends

//     //ImGui_ImplSDL2_InitForOpenGL(window, context);
//     ImGui_ImplOpenGL3_Init(glsl_version);

//     clear_color = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);//ImVec4(255 / 255.0f, 170 / 255.0f, 7 / 255.0f, 1.00f);

   
// };


//------------------------------------

// void GuiPreUpdate(SDL_Event event)
// {
//    // ImGui_ImplSDL2_ProcessEvent(&event);
//     glClear(GL_COLOR_BUFFER_BIT);

//     ImGui_ImplOpenGL3_NewFrame();
//     //ImGui_ImplSDL2_NewFrame();
//     ImGui::NewFrame();      

//  // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).

//     if (show_demo_window)
//         ImGui::ShowDemoWindow(&show_demo_window);

//     // // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
//     // {
//     //     static float f = 0.0f;
//     //     static int counter = 0;

//     //     ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

//     //     ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//     //     ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//     //     ImGui::Checkbox("Another Window", &show_another_window);

//     //     ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//     //     //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

//     //     if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//     //         counter++;
//     //     ImGui::SameLine();
//     //     ImGui::Text("counter = %d", counter);

//     //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

//     //     ImGui::End();
//     // }

//     // // 3. Show another simple window.
//     // if (show_another_window)
//     // {
//     //     ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
//     //     ImGui::Text("Hello from another window!");
//     //     if (ImGui::Button("Close Me"))
//     //         show_another_window = false;
//     //     ImGui::End();
//     // }
// };

//----------------------------------


// void RenderGui()
// {
//     ImGui::Render();
//     glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
//     glMatrixMode(GL_PROJECTION);
//     glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
//     glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//     //glClear(GL_COLOR_BUFFER_BIT);
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// }

//---------------------------------------------


// bool CloseGui()
// {
//     ImGui_ImplOpenGL3_Shutdown();
//     //ImGui_ImplSDL2_Shutdown();
//     ImGui::DestroyContext();

//     Log::write("GUI exited");

//     return false;
// }

//-------------------------------------------------------------- Initialize SDL


int InitializeWindow(Inputs* inputs)
{

   // SDL_Window* window;

    if(!glfwInit()) 
    {
        Log::error(glfwGetError(NULL));
        return -1;
    }
    else
    {

        Log::write("window initialized");
        
        glfwWindowHint(GLFW_DOUBLEBUFFER , 1);
        glfwWindowHint(GLFW_DEPTH_BITS, 24);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);

        // adjust these values depending on the OpenGL supported by your GPU driver
        
        std::string glsl_version = "";
        #ifdef __APPLE__
            // GL 3.2 + GLSL 150
            glsl_version = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            // required on Mac OS
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #elif __linux__
            // GL 3.2 + GLSL 150
            glsl_version = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        #elif _WIN32
            // GL 3.0 + GLSL 130
            glsl_version = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        #endif

            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef _WIN32
            // if it's a HighDPI monitor, try to scale everything
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            float xscale, yscale;
            glfwGetMonitorContentScale(monitor, &xscale, &yscale);
            std::cout << "[INFO] Monitor scale: " << xscale << "x" << yscale << std::endl;
            if (xscale > 1 || yscale > 1)
            {
                highDPIscaleFactor = xscale;
                glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            }
        #elif __APPLE__
            // to prevent 1200x800 from becoming 2400x1600
            // and some other weird resizings
            glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
        #endif

        //------------------- create window
                
            window = glfwCreateWindow(WIDTH, HEIGHT, "Spaghet about it!", NULL, NULL);

            if (!window)
            {
                glfwTerminate();
                return -1;
            }

            glfwMakeContextCurrent(window);
    
            //SDL_GL_SetSwapInterval(1); // Enable vsync

            glEnable(GL_TEXTURE_2D);
            glEnable(GL_BLEND);
            glBlendEquation(GL_FUNC_ADD);
           // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glGenTextures(3, TextureID/* &m_inst */); 
   

        //-----------main event stream

           // SDL_Event event;

        //------------Init game

          //  Game* game = new Game(inputs, TextureID);

        //-------- Init GUI

            //LaunchGui(glsl_version, inputs, event);

           // while (isRunning)
            //{
                // while (SDL_PollEvent(&event))
                // {
                //     bool res = inputs->pollInput(event, window);

                //     if (res == false)
                //         isRunning = false;

                //     GuiPreUpdate(event);
                //     game->Update(inputs);
                //     RenderGui();
                //     //SDL_GL_SwapWindow(window);  
                // }  
           // }

           while (!glfwWindowShouldClose(window))
           {

            //render

                glClear(GL_COLOR_BUFFER_BIT);

            //swap front and back buffers

                glfwSwapBuffers(window);

            //poll for process events

                glfwPollEvents();

           }


    //Cleanup

        //CloseGui();	

       // SDL_DestroyWindow(window);
        //SDL_GL_DeleteContext(context);

        //SDL_Delay( 2000 );
        IMG_Quit();
        SDL_Quit();

        //delete game;
        delete window;   
        
        Log::write("window closed");

        return 0;
    }
}



             
