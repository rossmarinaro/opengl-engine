
#include "../../headers/entity.h"
#include "../../headers/resources/spritesheets.h"

using namespace Entities;

void Sprite::Render()
{ 
    if (m_texture != NULL)
    {
        if (m_isSpritesheet == true)
        {
            if (m_currentFrame > m_frames)
                m_currentFrame = 0;
            m_currentFrameX = m_resourceData["frames"][m_currentFrame]["x"]; 
        }

        if (m_isAtlas == true || m_isSpritesheet == true)
            _SetSubTexture();

        else
           glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_texture->w, m_texture->h, 0, m_renderMode, GL_UNSIGNED_BYTE, m_texture->pixels);

    //render surface as open gl texture
    
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
    glPixelStorei(GL_UNPACK_ROW_LENGTH, m_texture->w);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, m_currentFrameX);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, m_currentFrameY);

    glTexImage2D(GL_TEXTURE_2D, 0, m_renderMode, m_currentFrameWidth, m_currentFrameHeight, 0, m_renderMode, GL_UNSIGNED_BYTE, m_texture->pixels);
    
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
}


//-----------------------------------------------------------


Sprite::Sprite(GLuint &id, float x, float y, const char* key[2])
{
    const char* spritesheet = Assets::Spritesheets::GetResource(key[0]); 
    SDL_Surface* image = IMG_Load(key[1]);

    if (image == NULL) 
        Log::error(SDL_GetError()); 
    else 
    { 
    //render image as opengl texture
    
        glBindTexture(GL_TEXTURE_2D, id);
        
        m_renderMode = GL_RGB;
        
        if (image->format->BytesPerPixel == 4) 
        { 
            m_renderMode = GL_RGBA; 
            Log::write("rgba enabled"); 
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Get image dimensions / position

        SetPosition(x, y);

        if (spritesheet != 0) 
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

        m_texture = image;
    
    }

    Log::write("Sprite instantiated");
}



