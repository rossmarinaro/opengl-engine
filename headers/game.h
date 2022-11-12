#pragma once

#include "./resources/assets.h"
#include "./renderer.h"
#include "./tilemap.h"
#include "./entity.h"


using namespace Entities;

class Game {
    
    private:

        static const bool m_gameState = true;
        const char* m_currentStage;
     
        Game* s_instance;
   

    public: 
    //static Player* m_player;
        AssetManager* m_assMgr;
        MapManager* m_mapMgr;

        static Inputs* inputs;

        static void Update(Inputs* inputs);

        Game(Inputs* inputs, GLuint TextureID[]);
        ~Game();

};
