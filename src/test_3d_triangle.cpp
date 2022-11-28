#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../vendors/glad/include/glad/glad.h"

#define _GLFW_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>


static const GLuint WIDTH = 800;
static const GLuint HEIGHT = 600;
/* ourColor is passed on to the fragment shader. */
static const GLchar* vertex_shader_source =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "out vec3 ourColor;\n"
    "uniform mat4 transform;\n"
    "void main() {\n"
    "    gl_Position = transform * vec4(position, 1.0f);\n"
    "    ourColor = color;\n"
    "}\n";
static const GLchar* fragment_shader_source =
    "#version 330 core\n"
    "in vec3 ourColor;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = vec4(ourColor, 1.0f);\n"
    "}\n";
static GLfloat vertices[] = {
/*   Positions          Colors */
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

/* Build and compile shader program, return its ID. */
GLuint common_get_shader_program(
    const char *vertex_shader_source,
    const char *fragment_shader_source
) {
    GLchar *log = NULL;
    GLint log_length, success;
    GLuint fragment_shader, program, vertex_shader;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);

    // if (log_length > 0) {
    //     glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
    //     printf("vertex shader log:\n\n%s\n", log);
    // }
    // if (!success) {
    //     printf("vertex shader compile error\n");
    //     exit(EXIT_FAILURE);
    // }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
    // if (log_length > 0) {

    //     glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
    //     printf("fragment shader log:\n\n%s\n", log);
    // }
    // if (!success) {
    //     printf("fragment shader compile error\n");
    //     exit(EXIT_FAILURE);
    // }

    /* Link shaders */
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
    // if (log_length > 0) {

    //     glGetProgramInfoLog(program, log_length, NULL, log);
    //     printf("shader link log:\n\n%s\n", log);
    // }
    // if (!success) {
    //     printf("shader link error");
    //     exit(EXIT_FAILURE);
    // }

    /* Cleanup. */
    free(log);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;
}

int main() {
    GLint shader_program;
    GLint transform_location;
    GLuint vbo;
    GLuint vao;
    GLFWwindow* window;
    double time;

    glfwInit();
    window = glfwCreateWindow(WIDTH, HEIGHT, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, WIDTH, HEIGHT);

    shader_program = common_get_shader_program(vertex_shader_source, fragment_shader_source);

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

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        transform_location = glGetUniformLocation(shader_program, "transform");
        /* THIS is just a dummy transform. */
        GLfloat transform[] = {
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f,
        };
        time = glfwGetTime();
        transform[0] = 2.0f * sin(time);
        transform[5] = 2.0f * cos(time);
        glUniformMatrix4fv(transform_location, 1, GL_FALSE, transform);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return EXIT_SUCCESS;
}