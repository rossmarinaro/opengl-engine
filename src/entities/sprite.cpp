  
#include "../../headers/entity.h"
#include "../../headers/resources/spritesheets.h"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb/stb_image.h"


using namespace Entities;

void Sprite::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);  
    glBindVertexArray(0);
}

//------------------------------------------ render sprite

void Sprite::Render (
    
    glm::vec2 position, 
    glm::vec2 size, 
    float rotate, 
    glm::vec3 color

)
{ 
    
    // prepare transformations

    m_shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position/* m_position */, 0.0f));  

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    
    if (rotate > 0)
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
    m_shader.SetMatrix4("model", model);
    m_shader.SetVector3f("spriteColor", color);
  
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture.ID);
   //tex.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    //old

    // if (m_isLoaded)
    // {
    
    //     //animation iteration
        
    //     if (m_isSpritesheet == true) 
    //     {
    //         if (m_currentFrame > m_frames)
    //             m_currentFrame = 0;
    //         m_currentFrameX = m_resourceData["frames"][m_currentFrame]["x"]; 
    //     }

    //     glPixelStorei(GL_UNPACK_ROW_LENGTH, m_width);
    //     glPixelStorei(GL_UNPACK_SKIP_PIXELS, m_currentFrameX); 
    //     glPixelStorei(GL_UNPACK_SKIP_ROWS, m_currentFrameY);

    //     glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_currentFrameWidth, m_currentFrameHeight, 0, m_renderMode, GL_UNSIGNED_BYTE, m_image);
        
    // //render open gl texture 

    //     glBegin(GL_QUADS);
    //         glTexCoord2f(0, 1); glVertex3f(m_posX, m_posY, 0);
    //         glTexCoord2f(1, 1); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY, 0);
    //         glTexCoord2f(1, 0); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY + m_srcHeight * m_scaleY, 0);
    //         glTexCoord2f(0, 0); glVertex3f(m_posX, m_posY + m_srcHeight * m_scaleY, 0); 
    //     glEnd();

    //     glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    //     glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    //     glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        
    //     glGenerateMipmap(GL_TEXTURE_2D);     
        
        

    // }

}


//-----------------------------------------------------------


Sprite::Sprite(glm::vec2 position, std::string name)
{

    this->m_position = position;

    const char* filepath = ResourceManager::GetAssetByKey(name).c_str();

    this->m_shader = ResourceManager::GetShader("sprite");
    this->m_shader.Use().SetInteger("image", 0);

    if (filepath != "NOT FOUND")
    {
       ResourceManager::LoadTexture(filepath, name);
       this->m_texture = ResourceManager::GetTexture(name);
       this->initRenderData();
    }


    //old

    // unsigned int id = m_id;
    
    // m_id = id;

    // glGenTextures(1, &m_id);

    // glBindTexture(GL_TEXTURE_2D, m_id);

    // int ok, w, h, channels;

    // ok = stbi_info(key[1], &w, &h, &channels);

    // m_width = w,
    // m_height = h;

    // m_renderMode = GL_RGB;
    
    // if (channels == 4) 
    // { 
    //     m_renderMode = GL_RGBA; 
    //     Log::write("rgba enabled"); 
    // }


    // //---------------- set the texture wrapping parameters

    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // // //--------------- set texture filtering parameters

    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // const char* spritesheet = Assets::Spritesheets::GetResource(key[0]); 

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
    // else
    // {
    //     m_currentFrameWidth = m_width; 
    //     m_currentFrameHeight = m_height;
    //     m_currentFrameX = 0;
    //     m_currentFrameY = 0; 
    // }

    // m_image = stbi_load(key[1], &m_width, &m_height, &channels, 0);  

    // if (!m_image) 
    //     Log::write("Error loading sprite."); 
        
    // else 
    // { 

    // //Get image dimensions / position

    //     SetPosition(-0.5, -0.5);
 
    //     m_isLoaded = true;
       
    //     Log::write("Sprite instantiated");

    // }

}

Sprite::~Sprite()
{

    //delete m_shader;
   // delete m_texture;

    glDeleteVertexArrays(1, &this->quadVAO);
    //stbi_image_free(m_image); 
    Log::write("Sprite Destroyed");

}
