#pragma once

#include "./renderer.h"
//#include "./tilemap.h"
#include "./entity.h"

#include "../headers/resources/manager.h"
#include "../headers/texture.h"

using namespace Entities;

class Game {
    
    private:

        static const bool m_gameState = true;
        const char* m_currentStage;
    
    public: 

       // MapManager* m_mapMgr;

        static Inputs* inputs;

        static void Update();

        Game();
        ~Game();

};
