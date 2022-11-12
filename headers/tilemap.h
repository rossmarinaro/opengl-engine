
#pragma once

#include "./entity.h"
#include "./game.h"

class MapManager {

    private:


        static const int m_mapWidth = 10 * 64;

        int m_mapTiles[100] = {
            1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        };

        // const uint32_t m_mapWidth = 10,
        //                m_mapHeight = 10,//strlen(m_mapTiles) / m_mapWidth;
        //                m_tileWidth = 64,
        //                m_tileHeight = 64;

    public:

        std::vector<Entities::TileSprite*> m_tilesprites;
        std::unordered_map<char, Entities::TileSprite*> m_textureMap;

        MapManager(GLuint &textureID, GLuint &textureID2, AssetManager* assets);
        ~MapManager(){
            delete[] m_mapTiles;
            m_textureMap.clear();
        };

};

