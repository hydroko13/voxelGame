#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../glerror/glerror.h"
#include "../shader/shader.h"

class Game {
    public:
        glm::ivec2 winSize;

        GLFWwindow *win;
        Shader shader1;

        Game();
        ~Game();

        int init();

        

        int run();

        
};

