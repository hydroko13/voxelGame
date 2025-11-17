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
#include "../blockSelectorBox/blockSelectorBox.h"
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

        float blockDestroyTick = 0.0f;
        int blockDestroyProgress = 0;

        double mx;
        double my;
        double time = 0.0;
        float dt;

        glm::ivec3 blockLookingAtPos;
        bool lookingAtABlock = false;


        glm::mat4 proj;
        
        BlockSelectorBox blockSelectorBox;

        Level level;


        Game();
        ~Game();

        int init();

        

        int run();

        
};

