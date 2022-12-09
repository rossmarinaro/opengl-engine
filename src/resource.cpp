
#include "../headers/resources/manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

// Instantiate static variables
std::map<std::string, Texture2D*> ResourceManager::Textures;
std::map<std::string, Shader*> ResourceManager::Shaders;
static std::vector<Shader*> shaderVector;
static std::vector<Texture2D*> textureVector;


static GLfloat vertices[] = {
/*   Positions          Colors */
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

Shader* ResourceManager::LoadShader(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader* ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D* ResourceManager::LoadTexture(const char *file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D* ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // delete all shaders	
    for (auto &shader : shaderVector)
        delete shader;
    // delete all textures
    for (auto &texture : textureVector)
        delete texture;
}

Shader* ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile)
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

    Shader* shader = new Shader(vertices, vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    shaderVector.push_back(shader);

    return shader; 
    
}

Texture2D* ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    //create texture object

    Texture2D* texture = new Texture2D;

    if (alpha)
    {
        texture->Internal_Format = GL_RGBA;
        texture->Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    // now generate texture
    texture->Generate(width, height, data);

    // and finally free image data
    stbi_image_free(data);

    textureVector.push_back(texture);

    return texture;
}