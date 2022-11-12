
// #include "../headers/game.h"
// #include "../headers/resources/assets.h"

// Sprite* background;
// Player* player;

// static std::vector<Sprite*> currentEntities;
// static std::vector<std::vector<TileSprite*>> map;


// Game::Game(Inputs* inputs, GLuint textures[]) 
// { 

// //init base systems

//     AssetManager* m_assMgr = new AssetManager();
//     MapManager* m_mapMgr = new MapManager(textures[0], textures[1], m_assMgr);

// //init entities

//     player = new Player(textures[2], -100.5, 0, m_assMgr->swanky_velvet);
//     //player->SetScale(0.325f, 0.75f); 

// //add entities to update queue

//     map.push_back(m_mapMgr->m_tilesprites);
//     currentEntities.push_back(player);
   
// }


// void Game::Update(Inputs* inputs)
// {

//     for (auto &layer : map)
//         for (auto &tile : layer)
//             tile->Render();

//     for (auto &ent : currentEntities)
//         ent == player ? 
//             player->Update(inputs) : ent->Render();
// }

// Game::~Game()
// {

//     for (auto &layer : map)
//         for (auto &tile : layer)
//             delete tile;

//     for (auto &ent : currentEntities)
//         delete ent;

//     delete m_mapMgr;
//     delete m_assMgr;   
    
//     Log::write("game closed.");
// }




