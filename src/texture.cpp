#include "../headers/texture.h"
#include "../headers/logs.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

void Texture::Render()
{ 
    if (m_isLoaded)
    {
        glActiveTexture(m_id);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        m_shader->use();
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        //--------

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, bytes);
        // glActiveTexture(GL_TEXTURE);
        // glBindTexture(GL_TEXTURE_2D, bytes2);

        // m_shader->use(); // don't forget to activate the shader before setting uniforms!  

        // glUniform1i(glGetUniformLocation(m_shader->ID, "texture"), 0); // set it manually
        // m_shader->setInt("texture2", 1); // or with shader class
        // glBindVertexArray(m_VAO);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        // while(...) 
        // {
        //     [...]
        // }

            

 

    }

}


Texture::Texture(GLuint id, GLuint texture, float x, float y, const char* key[2])
{

    m_shader = new Shader("assets/glsl/vert.shader", "assets/glsl/frag.shader"); 

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        //positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f  // top left 
    };

    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //---texture
    
    m_texture = texture;
    m_id = id;
    //glGenTextures(1, /* &id */&m_texture);
    //glActiveTexture(id);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    stbi_set_flip_vertically_on_load(true);  

    int ok, w, h, channels;

    ok = stbi_info(key[1], &w, &h, &channels);

    m_width = w,
    m_height = h;

    m_renderMode = GL_RGB;
    
    if (channels == 4) 
    { 
        m_renderMode = GL_RGBA; 
        Log::write("rgba enabled"); 
    }


    //---------------- set the texture wrapping parameters

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // //--------------- set texture filtering parameters

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //const char* spritesheet = Assets::Spritesheets::GetResource(key[0]); 

    // if (spritesheet != 0) //if spritesheet
    // {
    //     std::ifstream data(spritesheet);
    //     m_resourceData = json::parse(data);
    //     m_frames = m_resourceData["frames"].size() - 1;
    //     m_currentFrame = 0;
    //     m_currentFrameY = m_resourceData["frames"][m_currentFrame]["y"];
    //     m_currentFrameWidth = m_resourceData["frames"][m_currentFrame]["w"];
    //     m_currentFrameHeight = m_resourceData["frames"][m_currentFrame]["h"]; 
    //     m_isSpritesheet = true;
    // }  

    m_bytes = stbi_load(key[1], &m_width, &m_height, &channels, 0);  

    if (!m_bytes) 
        Log::write("Error loading sprite."); 
    else 
    { 

    //render Texture as opengl texture

        glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_width, m_height, 0, m_renderMode, GL_UNSIGNED_BYTE, m_bytes);
        glGenerateMipmap(GL_TEXTURE_2D);
       
        Log::write("Sprite instantiated");

        m_isLoaded = true;

        stbi_image_free(m_bytes);
    }


    //---tmp
    // unsigned int  texture2;
    // glGenTextures(1, &texture2);

    // glActiveTexture(GL_TEXTURE);
    // glBindTexture(GL_TEXTURE_2D, texture2);
 
    // glBindVertexArray(m_VAO);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // stbi_set_flip_vertically_on_load(true);  


    // ok = stbi_info("assets/Textures/swanky_velvet.png", &w, &h, &channels);


    // //glBindTexture(GL_TEXTURE_2D, texture);

    // m_renderMode = GL_RGB;
    
    // if (channels == 4) 
    // { 
    //     m_renderMode = GL_RGBA; 
    //     Log::write("rgba enabled"); 
    // }

    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // // set the texture wrapping parameters

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // // set texture filtering parameters

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // unsigned char* Texture2 = stbi_load("assets/Textures/swanky_velvet.png", &m_width, &m_height, &channels, 0);  

    // if (!Texture2) 
    //     Log::write("Error loading sprite."); 
    // else 
    // { 

    // //render Texture as opengl texture

    //     glTexTexture2D(GL_TEXTURE_2D, 0, m_renderMode, m_width, m_height, 0, m_renderMode, GL_UNSIGNED_BYTE, Texture2);
    //     glGenerateMipmap(GL_TEXTURE_2D);

    //     bytes2 = texture2;
       
       
    //     Log::write("Sprite instantiated");


    //     stbi_Texture_free(Texture2);
    // }



}


Texture::~Texture()
{

    Log::write("Sprite Destroyed");
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    delete m_shader;
}