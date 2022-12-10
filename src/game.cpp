
#include "../headers/game.h"
#include "../headers/window.h"


//Sprite* menu;
//Player* player;

static std::vector<Sprite*> currentEntities;
static std::vector<std::vector<TileSprite*>> map;


Sprite* sprite;
Sprite* sprite2;

Game::Game() 
{ 

    //init base systems

    m_resMgr.InitializeResources();
   
    //MapManager* m_mapMgr = new MapManager(m_assMgr);

    //init entities

      
   // menu = new Sprite(-100.5, 0, m_assMgr.pastaboss);     
   // player = new Player(0, 0, m_assMgr.swanky_velvet);


    //add entities to update queue
    
  //  currentEntities.push_back(menu); 
    //currentEntities.push_back(player);
    //map.push_back(m_mapMgr->m_tilesprites); 

    sprite2 = new Sprite(glm::vec2(400.0f, 300.0f), "swanky velvet");
    sprite = new Sprite(glm::vec2(300.0f, 200.0f), "swanky velvet");

  
}

//----------------------------------

void Game::Update()
{

    // for (auto &layer : map)
    //     for (auto &tile : layer)
    //         tile->Render();

    // for (auto &ent : currentEntities)
    //     ent == player ? 
    //         player->Update() : ent->Render();

    // for (auto &ent : currentTextures)
    //     ent->Render();

   sprite2->Render(glm::vec2(400.0f, 400.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
  // sprite->Render(glm::vec2(300.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

}

Game::~Game()
{

 delete sprite; delete sprite2;

    // for (auto &layer : map)
    //     for (auto &tile : layer)
    //         delete tile;

    // for (auto &ent : currentEntities)
    //     delete ent;

    //delete m_mapMgr;
 //   delete m_resMgr;   
    
    Log::write("game closed.");
}




