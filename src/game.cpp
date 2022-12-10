
#include "../headers/game.h"
#include "../headers/resources/assets.h"
#include "../headers/resources/manager.h"
#include "../headers/texture.h"

#include "../headers/window.h"


//Sprite* menu;
//Player* player;

static std::vector<Sprite*> currentEntities;
static std::vector<std::vector<TileSprite*>> map;


// Texture* tex1;
// Texture* tex2;

// static std::vector<Texture*> currentTextures;
 AssetManager* m_assMgr;
 Shader* shadeA;
 Shader* shadeB;
 Texture2D* tex;
 Sprite* renderable;

Game::Game() 
{ 


    //init base systems

    //AssetManager m_assMgr;
    //MapManager* m_mapMgr = new MapManager(m_assMgr);

    //init entities
 
        // tex1 = new Texture(/* GL_TEXTURE0, tex[0], */ 0, 0, m_assMgr.pastaboss);
        // tex2 = new Texture(/* GL_TEXTURE1, tex[1], */ 0, 0, m_assMgr.menu);
        // currentTextures.push_back(tex1);
        // currentTextures.push_back(tex2);

      
   // menu = new Sprite(-100.5, 0, m_assMgr.pastaboss);     
   // player = new Player(0, 0, m_assMgr.swanky_velvet);


    //add entities to update queue
    
  //  currentEntities.push_back(menu); 
    //currentEntities.push_back(player);
    //map.push_back(m_mapMgr->m_tilesprites); 


    ResourceManager::LoadShader("assets/glsl/projection/vert.shader", "assets/glsl/projection/frag.shader", nullptr, "sprite");

    shadeA = ResourceManager::GetShader("sprite");
    
    shadeA->Use(); 
    shadeA->SetInteger("image", 0, true);

    //shadeB = ResourceManager::GetShader("sprite");
    
    //set render-specific controls
    renderable = new Sprite(*shadeA);
    // load textures
    ResourceManager::LoadTexture("assets/images/swanky_velvet.png", true, "swanky_velvet");
            
    tex = ResourceManager::GetTexture("swanky_velvet");


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

//    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Window::width), static_cast<float>(Window::height), 0.0f, -1.0f, 1.0f);
//    shadeB->SetMatrix4("projection", projection,true);
   renderable->Render(tex, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

}

Game::~Game()
{
 delete shadeA;
 delete shadeB;
 delete tex;
 delete renderable;
    // for (auto &layer : map)
    //     for (auto &tile : layer)
    //         delete tile;

    // for (auto &ent : currentEntities)
    //     delete ent;

    //delete m_mapMgr;
    delete m_assMgr;   
    
    Log::write("game closed.");
}




