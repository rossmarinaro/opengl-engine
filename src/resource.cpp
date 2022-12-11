
#include "../headers/resources/manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, std::string> ResourceManager::m_assets;

static std::vector<Shader> shaderVector;
static std::vector<Texture2D> textureVector;


static GLfloat vertices[] = {
/*   Positions          Colors */
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

void ResourceManager::InitializeResources()
{

    m_assets.insert({
        { "menu", "assets/images/menu.png" },
        { "pastaboss", "assets/images/pb.png" },
        { "swanky velvet", "assets/images/swanky_velvet.png" },
        { "map", "assets/images/map.png" },
        { "brick", "assets/images/brick.png" }
    });


    Log::write("resources initialized");
}

std::string ResourceManager::GetAssetByKey(std::string name)
{
    std::map<std::string, std::string>::iterator iterator;

    iterator = m_assets.find(name);

    return iterator != m_assets.end() ? 
           iterator->second : "NOT FOUND";      
}

void ResourceManager::Clear()
{
    
    for (auto shader : Shaders)
    {
        glDeleteVertexArrays(1, &shader.second.VAO);
        glDeleteBuffers(1, &shader.second.VBO);
        glDeleteProgram(shader.second.ID);
    }
    for (auto tex : Textures)
    {
        glDeleteTextures(1, &tex.second.ID);   
        glBindTexture(GL_TEXTURE_2D, 0); 
    }

}

//------------------------------------- shaders

Shader ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath

    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try
    {

    // open files

        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

    // read file's buffer contents into streams

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

    // close file handlers

        vertexShaderFile.close();
        fragmentShaderFile.close();

    // convert stream into string

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    // if geometry shader path is present, also load a geometry shader

        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        Log::write("ERROR::SHADER: Failed to read shader files");
    }
    
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    // 2. now create shader object from source code

    Shader shader; 

    shader.Init(vertices, vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    return shader; 
    
}

//------------------------------- textures

Texture2D ResourceManager::LoadTexture(const char* file, std::string name)
{
    Textures[name] = loadTextureFromFile(file);
    return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

Texture2D ResourceManager::loadTextureFromFile(const char* file)
{
    //create texture object / load image

    Texture2D texture;

    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    if (nrChannels == 4)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    
    texture.Generate(width, height, data);

    stbi_image_free(data);

    return texture;
}

