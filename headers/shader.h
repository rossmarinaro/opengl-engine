#ifndef SHADER_H
#define SHADER_H

#include "../vendors/glad/include/glad/glad.h"
#include "./logs.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {


public:

    // -------------------------------------------------- utility functions

    void    SetFloat    (const char *name, float value, bool useShader = false);
    void    SetInteger  (const char *name, int value, bool useShader = false);
    void    SetVector2f (const char *name, float x, float y, bool useShader = false);
    void    SetVector2f (const char *name, const glm::vec2 &value, bool useShader = false);
    void    SetVector3f (const char *name, float x, float y, float z, bool useShader = false);
    void    SetVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
    void    SetVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    void    SetVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
    void    SetMatrix4  (const char *name, const glm::mat4 &matrix, bool useShader = false);

    // --------------------------------------------------- constructor generates the shader on the fly 
void Init(GLfloat vertices[], const char* vertexPath, const char* fragmentPath, const char* geomPath = nullptr);
  //  Shader() = default;
    Shader(/* GLfloat vertices[], const char* vertexPath, const char* fragmentPath, const char* geomPath = nullptr */){};
    //~Shader();

    // --------------------------------------------------- activate the shader

    Shader& Use();

    void transform(GLfloat transformation[]);

    unsigned int ID;
        GLuint VBO;
    GLuint VAO;
private:
            
   // unsigned int ID;
    GLint transform_location;
    // GLuint VBO;
    // GLuint VAO;

    // --------------------------------------------------- check compilation/linking errors.

    void checkCompileErrors(unsigned int shader, std::string type);

};

#endif





