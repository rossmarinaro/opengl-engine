#include "./shader.h"
    
class Texture {
    
    public:

        Shader* m_shader;
        
        unsigned int m_VBO, 
                     m_VAO,     
                     m_EBO, 
                     m_texture1, 
                     m_texture2;

        Texture(float x, float y, const char* key[2]);
        ~Texture();
};