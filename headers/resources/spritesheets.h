#pragma once

#include <string>
#include <vector>

using string = std::string;

namespace Assets {

    namespace Spritesheets {


        enum Options {
            menu,
            swanky_velvet,
            map
        };

        Options resolveString(string const &input)
        {
            if (input == "swanky_velvet") 
                return swanky_velvet;

        };

        const char* GetResource(string key)
        {
            switch (resolveString(key))
            {
                case swanky_velvet:
                    return "assets/json/anims/swanky_velvet.json";
   

                //--------- no spritesheet
                
                default:
                    return 0;

            }
        }


    }
}

