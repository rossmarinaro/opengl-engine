#pragma once

#include <map>



class AssetManager
{
    public:

        const char* menu[2] = { "menu", "assets/images/menu.png" };
        const char* swanky_velvet[2] = { "swanky_velvet", "assets/images/swanky_velvet.png" };
        const char* map[2] = { "map", "assets/images/map.png" };
        const char* brick[2] = { "brick", "assets/images/brick.png" };

        AssetManager(){};
        ~AssetManager(){};
};