
#include "../headers/game.h"
#include "../headers/resources/assets.h"
#include "../headers/texture.h"


Sprite* menu;
Player* player;

static std::vector<Sprite*> currentEntities;
static std::vector<std::vector<TileSprite*>> map;


// Texture* tex1;
// Texture* tex2;

// static std::vector<Texture*> currentTextures;



Game::Game() 
{ 

    //init base systems

    AssetManager m_assMgr;
    MapManager* m_mapMgr = new MapManager(m_assMgr);

    //init entities
 
        // tex1 = new Texture(/* GL_TEXTURE0, tex[0], */ 0, 0, m_assMgr.pastaboss);
        // tex2 = new Texture(/* GL_TEXTURE1, tex[1], */ 0, 0, m_assMgr.menu);
        // currentTextures.push_back(tex1);
        // currentTextures.push_back(tex2);

      
   // menu = new Sprite(-100.5, 0, m_assMgr.pastaboss);     
    player = new Player(0, 0, m_assMgr.swanky_velvet);


    //add entities to update queue
    
  //  currentEntities.push_back(menu); 
    currentEntities.push_back(player);
    map.push_back(m_mapMgr->m_tilesprites); 
            
   

}

//----------------------------------

void Game::Update()
{

    for (auto &layer : map)
        for (auto &tile : layer)
            tile->Render();

    for (auto &ent : currentEntities)
        ent == player ? 
            player->Update() : ent->Render();

    // for (auto &ent : currentTextures)
    //     ent->Render();


}

Game::~Game()
{

    for (auto &layer : map)
        for (auto &tile : layer)
            delete tile;

    for (auto &ent : currentEntities)
        delete ent;

    delete m_mapMgr;
    delete m_assMgr;   
    
    Log::write("game closed.");
}




