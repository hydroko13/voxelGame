#pragma once


#include <stb_image.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

class Game {
    public:
        glm::ivec2 winSize;

        GLFWwindow *win;

        Game();
        ~Game();

        int init();

        

        int run();

        
};

