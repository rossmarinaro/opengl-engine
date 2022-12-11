#include "../headers/shader.h"


    void Shader::Init(GLfloat vertices[], const char* vertexPath, const char* fragmentPath, const char* geomPath)
    {

        // 2. compile shaders

        unsigned int vertex, fragment, geometry;

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


        // if geometry shader 

        if (geomPath != nullptr)
        {
            geometry = glCreateShader(GL_GEOMETRY_SHADER);
            glShaderSource(geometry, 1, &geomPath, NULL);
            glCompileShader(geometry);
            checkCompileErrors(geometry, "GEOMETRY");
        }

        // shader Program

        this->ID = glCreateProgram();
        glAttachShader(this->ID, vertex);
        glAttachShader(this->ID, fragment);

        if (geomPath != nullptr)
            glAttachShader(this->ID, geometry);

        glLinkProgram(this->ID);
        checkCompileErrors(this->ID, "PROGRAM");

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

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

        // delete the shaders

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        if (geomPath != nullptr)
            glDeleteShader(geometry);
    }
    
    // Shader::~Shader()
    // {
    //     glDeleteVertexArrays(1, &VAO);
    //     glDeleteBuffers(1, &VBO);
    //     glDeleteProgram(this->ID);
    // }

    // ------------------------------------------------------------------------ activate 

    Shader& Shader::Use() 
    { 
        glUseProgram(this->ID); 
        return *this;
    }

    //-------------------------------------------------------------------------- transform

    void Shader::transform(GLfloat transformation[])
    {
        transform_location = glGetUniformLocation(ID, "transform");
        glUniformMatrix4fv(transform_location, 1, GL_FALSE, transformation);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

    }

    void Shader::checkCompileErrors(unsigned int shader, std::string type)
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


    // utility uniform functions

    // -----------------------------------------------------------------------

    void Shader::SetFloat(const char *name, float value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1f(glGetUniformLocation(this->ID, name), value);
    }

    // -----------------------------------------------------------------------

    void Shader::SetInteger(const char *name, int value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform1i(glGetUniformLocation(this->ID, name), value);
    }

    // -----------------------------------------------------------------------

    void Shader::SetVector2f(const char *name, float x, float y, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->ID, name), x, y);
    }

    // -----------------------------------------------------------------------

    void Shader::SetVector2f(const char *name, const glm::vec2 &value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
    }

    // -----------------------------------------------------------------------

    void Shader::SetVector3f(const char *name, float x, float y, float z, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
    }

    // -----------------------------------------------------------------------

    void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
    }

    // -----------------------------------------------------------------------

    void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
    }

    // -----------------------------------------------------------------------

    void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
    }

    // -----------------------------------------------------------------------

    void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
    {
        if (useShader)
            this->Use();
        glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(matrix));
    }