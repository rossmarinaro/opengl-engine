
#include "../headers/game.h"
#include "../headers/window.h"


//Sprite* menu;
//Player* player;

static std::vector<Sprite*> currentEntities;
static std::vector<std::vector<TileSprite*>> map;


Sprite* sprite;
Sprite* player;

Game::Game() 
{ 

    //init base systems

    ResourceManager::InitializeResources();
   
    //MapManager* m_mapMgr = new MapManager(m_assMgr);

    //init entities


    sprite = new Sprite(glm::vec2(600.0f, 400.0f), "swanky velvet");
    player = new Sprite(glm::vec2(600.0f, 400.0f), "pastaboss");

   // menu = new Sprite(-100.5, 0, m_assMgr.pastaboss);     
   // player = new Player(0, 0, m_assMgr.swanky_velvet);
   // sprite = new Sprite(glm::vec2(400.0f, 300.0f), "swanky velvet");
    //player = new Sprite(glm::vec2(300.0f, 200.0f), "swanky velvet");

    //add entities to update queue
    
    currentEntities.push_back(sprite); 
    currentEntities.push_back(player);
    //map.push_back(m_mapMgr->m_tilesprites); 



}

//----------------------------------

void Game::Update()
{
    // for (auto &layer : map)
    //     for (auto &tile : layer)
    //         tile->Render();

    for (auto &ent : currentEntities)
        ent == player ? 
            player->Render(glm::vec2(500.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f))
             /* Update() */ : ent->Render(glm::vec2(400.0f, 200.0f), glm::vec2(300.0f, 400.0f), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

}

Game::~Game()
{

 delete sprite; delete player;

    // for (auto &layer : map)
    //     for (auto &tile : layer)
    //         delete tile;

    // for (auto &ent : currentEntities)
    //     delete ent;

    //delete m_mapMgr;
 //   delete m_resMgr;   
    
    Log::write("game closed.");
}




