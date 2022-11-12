
#include "../../headers/entity.h"

using namespace Entities;

enum anims {
    jump, 
    walk,
    idle
};

anims parseString(string const &string)
{
    if (string == "jump") return jump;
    if (string == "walk") return walk;
    if (string == "idle") return idle;
}

 
//-----------------------------------------------------------

void Player::Animate(string animKey)
{
    switch (parseString(animKey))
    {
        case idle:

        break;
        case jump: 
        
        break;
        case walk:

            m_currentFrame++;
           

        break;
    }
}

//---------------------------------------------------

void Player::Update(Inputs* inputs)
{
    // Uint32 ticks = SDL_GetTicks();
    // Uint32 seconds = ticks / 1000;
    // Uint32 spriteFrame = seconds % 3;//4;       
  

    if (inputs->m_right == true)
    {
        m_posX += 0.01f;    
        Animate("walk");
    }
    if (inputs->m_left == true)
    {
        m_posX -= 0.01f;
        Animate("walk");
    }
    if (inputs->m_down == true)
    {
        m_posY += 0.01f; 
        Animate("jump");
    }
    if (inputs->m_up == true)
    {
        m_posY -= 0.01f;
        Animate("jump"); 
    }

    Render();

}

