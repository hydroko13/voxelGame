#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../glerror/glerror.h"
#include "../shader/shader.h"
#include "../shaderProgram/shaderProgram.h"
#include "../vertexArray/vertexArray.h"
#include "../vertexBuffer/vertexBuffer.h"
#include "../elementBuffer/elementBuffer.h"

class Game {
    public:
        glm::ivec2 winSize;

        GLFWwindow *win = nullptr;
        ShaderProgram shaderProgram1;
        VertexBuffer VBO;
        VertexArray VAO;
        ElementBuffer EBO;

        float vertices[12] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        };

        unsigned int indices[6] = {
            0, 1, 2,
            0, 3, 2,
        };
        

        
        

        Game();
        ~Game();

        int init();

        

        int run();

        
};

