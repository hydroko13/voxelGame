#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <tuple>
#include "../glerror/glerror.h"
#include "../shader/shader.h"
#include "../shaderProgram/shaderProgram.h"
#include "../vertexArray/vertexArray.h"
#include "../vertexBuffer/vertexBuffer.h"
#include "../elementBuffer/elementBuffer.h"
#include "../image/image.h"
#include "../texture/texture.h"
#include "../camera/camera.h"
#include "../imageAtlas/imageAtlas.h"
#include "../blockRegistry/blockRegistry.h"
#include "../block/block.h"
#include "../chunk/chunk.h"
#include "../level/level.h"
#include <chrono>
#include <cmath>




class Game {
    public:
        glm::ivec2 winSize;

        GLFWwindow *win = nullptr;
        ShaderProgram shaderProgram1;
        Texture tex;
        Camera camera;
        ImageAtlas blockAtlas;
        BlockRegistry blockRegistry;

        float vertices[20] = {
        -0.5f, -0.5f, 0.0f,    0.0, 0.0f,
        -0.5f, 0.5f, 0.0f,     0.0, 1.0f,
        0.5f, 0.5f, 0.0f,      1.0, 1.0f,
        0.5f, -0.5f, 0.0f,     1.0, 0.0f
        };

        unsigned int indices[6] = {
            0, 1, 2,
            2, 3, 0
        };
        

        double mx;
        double my;

        glm::mat4 proj;
        
        Level level;


        Game();
        ~Game();

        int init();

        

        int run();

        
};

