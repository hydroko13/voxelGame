#pragma once

#include <stb_image.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

class Shader {

    private:
        GLuint shader_gpu_handle;
        GLenum shader_type;
        const char* fp;
        std::string shader_source_code;

    public:
        Shader(GLenum shader_type, const char* fp);
        ~Shader();

        int init();

        void use();

        void compile();

        
};


