
#include "../headers/game.h"
#include "../headers/resources/assets.h"
#include "../headers/texture.h"


Player* player;
Sprite* menu;


static std::vector<Sprite*> currentEntities;
static std::vector<std::vector<TileSprite*>> map;


Texture* tex1;
Texture* tex2;

static std::vector<Texture*> currentTextures;
GLuint tex[2];


Game::Game(GLuint textures[]) 
{ 

    //init base systems

      AssetManager* m_assMgr = new AssetManager();
      //  MapManager* m_mapMgr = new MapManager(textures[0], textures[1], m_assMgr);

    //init entities
 
        // tex1 = new Texture(GL_TEXTURE0, tex[0], 0, 0, m_assMgr->pastaboss);
        // tex2 = new Texture(GL_TEXTURE1, tex[1], 0, 0, m_assMgr->menu);
        // currentTextures.push_back(tex1);
        // currentTextures.push_back(tex2);

       menu = new Sprite(textures[0], 0, 0, m_assMgr->menu);
       player = new Player(textures[1], -100.5, 0, m_assMgr->swanky_velvet);
       player->SetScale(0.325f, 0.75f); 

    ////add entities to update queue

       //map.push_back(m_mapMgr->m_tilesprites);
       currentEntities.push_back(menu);      
       currentEntities.push_back(player);

}


void Game::Update()
{

    // for (auto &layer : map)
    //     for (auto &tile : layer)
    //         tile->Render();

    for (auto &ent : currentEntities)
        ent == player ? 
            player->Update() : ent->Render();

    // for (auto &ent : currentTextures)
    //     ent->Render();
}

Game::~Game()
{

    /* for (auto &layer : map)
        for (auto &tile : layer)
            delete tile; */

    for (auto &ent : currentEntities)
        delete ent;

    //delete m_mapMgr;
    delete m_assMgr;   
    
    Log::write("game closed.");
}




