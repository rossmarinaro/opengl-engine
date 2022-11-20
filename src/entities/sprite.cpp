  
#include "../../headers/entity.h"
#include "../../headers/resources/spritesheets.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


using namespace Entities;

unsigned int currentTextures;
GLuint* textures;


void Sprite::Render()
{ 
    if (m_texture1 != NULL)
    {

        if (m_isSpritesheet == true)
        {
            if (m_currentFrame > m_frames)
                m_currentFrame = 0;
            m_currentFrameX = m_resourceData["frames"][m_currentFrame]["x"]; 
        }

        if (m_isAtlas == true || m_isSpritesheet == true)
            _SetSubTexture();

       //render surface as open gl texture (works)
    
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex3f(m_posX, m_posY, 0);
            glTexCoord2f(1, 1); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY, 0);
            glTexCoord2f(1, 0); glVertex3f(m_posX + m_srcWidth * m_scaleX, m_posY + m_srcHeight * m_scaleY, 0);
            glTexCoord2f(0, 0); glVertex3f(m_posX, m_posY + m_srcHeight * m_scaleY, 0); 
        glEnd();

    
    }

}

//-----------------------------------------------------------

void Sprite::_SetSubTexture()
{
    glPixelStorei(GL_UNPACK_ROW_LENGTH, m_width);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, m_currentFrameX);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, m_currentFrameY);

    glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_currentFrameWidth, m_currentFrameHeight, 0, m_renderMode, GL_UNSIGNED_BYTE, m_image1);
    //glTexSubImage2D(GL_TEXTURE_2D, 0, m_currentFrameWidth, m_currentFrameHeight, m_width, m_height, m_renderMode, GL_UNSIGNED_BYTE, m_image1);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

}

//-----------------------------------------------------------

Sprite::Sprite(unsigned int &id, float x, float y, const char* key[2])
{


    //---texture
    
    unsigned int texture1;
    
    glGenTextures(1, /* &id */ &texture1 );
    glBindTexture(GL_TEXTURE_2D, /* id */ texture1);


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

    m_image1 = stbi_load(key[1], &m_width, &m_height, &channels, 0);  

    if (!m_image1) 
        Log::write("Error loading sprite."); 
    else 
    { 

    //render image as opengl texture

        glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_width, m_height, 0, m_renderMode, GL_UNSIGNED_BYTE, m_image1);
        glGenerateMipmap(GL_TEXTURE_2D);

    //Get image dimensions / position

        SetPosition(-0.5, -0.5);
 
        m_texture1 = texture1; //id;
       
        Log::write("Sprite instantiated");

        stbi_image_free(m_image1);
    }

}

Sprite::~Sprite()
{

    Log::write("Sprite Destroyed");

}