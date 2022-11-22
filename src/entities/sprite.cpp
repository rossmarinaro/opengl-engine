  
#include "../../headers/entity.h"
#include "../../headers/resources/spritesheets.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


using namespace Entities;


void Sprite::Render()
{ 
    if (m_isLoaded)
    {
    
        //animation iteration
        
        if (m_isSpritesheet == true) 
        {
            if (m_currentFrame > m_frames)
                m_currentFrame = 0;
            m_currentFrameX = m_resourceData["frames"][m_currentFrame]["x"]; 
        }

        glPixelStorei(GL_UNPACK_ROW_LENGTH, m_width);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, m_currentFrameX);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, m_currentFrameY);

        glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_currentFrameWidth, m_currentFrameHeight, 0, m_renderMode, GL_UNSIGNED_BYTE, m_image);
        
    //render open gl texture 

        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex3f(m_posX, m_posY, 0);
            glTexCoord2f(1, 1); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY, 0);
            glTexCoord2f(1, 0); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY + m_srcHeight * m_scaleY, 0);
            glTexCoord2f(0, 0); glVertex3f(m_posX, m_posY + m_srcHeight * m_scaleY, 0); 
        glEnd();

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }

}


//-----------------------------------------------------------


Sprite::Sprite(float x, float y, const char* key[2])
{

    unsigned int id = m_id;
    
    m_id = id;

    glGenTextures(1, &m_id);

    glBindTexture(GL_TEXTURE_2D, m_id);

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

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // //--------------- set texture filtering parameters

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    const char* spritesheet = Assets::Spritesheets::GetResource(key[0]); 

    if (spritesheet != 0) //if spritesheet
    {
        std::ifstream data(spritesheet);
        m_resourceData = json::parse(data);
        m_frames = m_resourceData["frames"].size() - 1;
        m_currentFrame = 0;
        m_currentFrameY = m_resourceData["frames"][m_currentFrame]["y"];
        m_currentFrameWidth = m_resourceData["frames"][m_currentFrame]["w"];
        m_currentFrameHeight = m_resourceData["frames"][m_currentFrame]["h"]; 
        m_isSpritesheet = true;
    }  
    else
    {
        m_currentFrameWidth = m_width; 
        m_currentFrameHeight = m_height;
        m_currentFrameX = 0;
        m_currentFrameY = 0; 
    }

    m_image = stbi_load(key[1], &m_width, &m_height, &channels, 0);  

    if (!m_image) 
        Log::write("Error loading sprite."); 
        
    else 
    { 

    //Get image dimensions / position

        SetPosition(-0.5, -0.5);
 
        m_isLoaded = true;
       
        Log::write("Sprite instantiated");

    }

}

Sprite::~Sprite()
{

    stbi_image_free(m_image); 
    Log::write("Sprite Destroyed");

}


/* 
timer:

double prevTime = glfwGetTime();

while...
double currTime = glfwGetTime();
if (currTime - prevTime >= 1/ 60)
{
    do something...
    prevTime = currTime
}


 */