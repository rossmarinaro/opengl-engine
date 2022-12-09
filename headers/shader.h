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
 
    // constructor
    Shader() { }
    // sets the current shader as active
  //  Shader  &Use();

    // utility functions
    // void    SetFloat    (const char *name, float value, bool useShader = false);
    // void    SetInteger  (const char *name, int value, bool useShader = false);
    // void    SetVector2f (const char *name, float x, float y, bool useShader = false);
    // void    SetVector2f (const char *name, const glm::vec2 &value, bool useShader = false);
   // void    SetVector3f (const char *name, float x, float y, float z, bool useShader = false);
   // void    SetVector3f (const char *name, const glm::vec3 &value, bool useShader = false);
    // void    SetVector4f (const char *name, float x, float y, float z, float w, bool useShader = false);
    // void    SetVector4f (const char *name, const glm::vec4 &value, bool useShader = false);
    // void    SetMatrix4  (const char *name, const glm::mat4 &matrix, bool useShader = false);

    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(GLfloat vertices[], const char* vertexPath, const char* fragmentPath, const char* geomPath = nullptr)
    {


        // 2. compile shaders

        unsigned int vertex, fragment, gShader;

        // vertex shader

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexPath, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        // fragment Shader

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentPath, NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");


    // if geometry shader source code is given, also compile geometry shader
        if (geomPath != nullptr)
        {
            gShader = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(gShader, 1, &geomPath, NULL);
            glCompileShader(gShader);
            checkCompileErrors(gShader, "GEOMETRY");
        }

        // shader Program

        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertex);
        glAttachShader(this->ID, fragment);

        if (geomPath != nullptr)
            glAttachShader(this->ID, gShader);

        glLinkProgram(this->ID);
        checkCompileErrors(this->ID, "PROGRAM");

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /* Position attribute */

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        /* Color attribute */

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1); 
        glBindVertexArray(0);

        //use program

        this->Use();         
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        if (geomPath != nullptr)
            glDeleteShader(gShader);
    }
    ~Shader()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteProgram(this->ID);
        Log::write("shader deleted");
    }


    
    // activate the shader
    // ------------------------------------------------------------------------
    Shader& Use() 
    { 
        glUseProgram(this->ID); 
        return *this;
    }

    void transform(GLfloat transformation[])
    {
        transform_location = glGetUniformLocation(ID, "transform");
        glUniformMatrix4fv(transform_location, 1, GL_FALSE, transformation);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    // void setBool(const std::string &name, bool value) const
    // {         
    //     glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value); 
    // }
    // // ------------------------------------------------------------------------ 
    // void setInt(const std::string &name, int value) const
    // { 
    //     glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value); 
    // }
    // // ------------------------------------------------------------------------
    // void setFloat(const std::string &name, float value) const
    // { 
    //     glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value); 
    // }

    //new

    // void SetFloat(const char *name, float value, bool useShader)
    // {
    //     if (useShader)
    //         this->Use();
    //     glUniform1f(glGetUniformLocation(this->ID, name), value);
    // }
    void SetInteger(const char *name, int value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1i(glGetUniformLocation(this->ID, name), value);
    }
    // void SetVector2f(const char *name, float x, float y, bool useShader)
    // {
    //     if (useShader)
    //         this->Use();
    //     glUniform2f(glGetUniformLocation(this->ID, name), x, y);
    // }
    // void SetVector2f(const char *name, const glm::vec2 &value, bool useShader)
    // {
    //     if (useShader)
    //         this->Use();
    //     glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
    // }
    // void SetVector3f(const char *name, float x, float y, float z, bool useShader)
    // {
    //     if (useShader)
    //         this->Use();
    //     glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
    // }
    void SetVector3f(const char *name, const glm::vec3 &value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
    }
    // void SetVector4f(const char *name, float x, float y, float z, float w, bool useShader)
    // {
    //     if (useShader)
    //         this->Use();
    //     glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
    // }
    // void SetVector4f(const char *name, const glm::vec4 &value, bool useShader)
    // {
    //     if (useShader)
    //         this->Use();
    //     glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
    // }
    void SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
    }

private:


    unsigned int ID;
    GLint transform_location;
    GLuint vbo;
    GLuint vao;

    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                Log::write("ERROR1::SHADER_COMPILATION_ERROR of type: ");
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                Log::write("ERROR2::SHADER_COMPILATION_ERROR of type: ");
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

#endif







//cpp







