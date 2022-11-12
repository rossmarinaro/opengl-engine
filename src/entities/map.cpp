#include "../../headers/game.h"
#include "../../headers/logs.h"
#include "../../headers/tilemap.h"

#include "../../vendors/nlohmann/json.hpp"
#include "../../vendors/tileson/tileson.hpp" 

using json = nlohmann::json;

MapManager::MapManager(GLuint &textureID, GLuint &textureID2, AssetManager* assets)
{
    int width = 0, 
        height = 0;

    for (int tile = 0; tile < 100; tile++)
    {
        if (width < 10)
            width++;

        if (height < 10)
            height++;
            
        int 
            posX = width * 64,
            posY = height * 64;

        if (m_mapTiles[tile] == 0)
            m_textureMap[0] = new Entities::TileSprite(textureID2, posX, posY, 0, 0, assets->map);
        if (m_mapTiles[tile] == 1)
            m_textureMap[1] = new Entities::TileSprite(textureID2, posX, posY, 576, 576, assets->map);
    }    
    
   

   
}

