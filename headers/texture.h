#include "./shader.h"
    
class Texture {
    
    public:

        Shader* m_shader;

        int m_frames, 
            m_width,
            m_height,
            m_currentFrame;

        void Render();
        Texture(float x, float y, const char* key[2]);
        ~Texture();

    private:

        unsigned char* m_bytes;
        bool m_isLoaded = false;
        unsigned int 
                     m_VBO, 
                     m_VAO,     
                     m_EBO;
        GLuint m_id;
        int m_renderMode;
};