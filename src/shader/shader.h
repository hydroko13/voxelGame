#pragma once


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../glerror/glerror.h"
#include <string>
#include <fstream>
#include <filesystem>

enum class ShaderStatus {
    CompiledSuccessfully,
    CompileFailed,
    InitializedSuccessfully,
    FileOpenFailed,
};



class Shader {

    private:
        GLuint shader_gpu_handle = NULL;
        GLenum shader_type = NULL;
        std::string filename;

        std::string shader_source_code;
        

    public:

        Shader();
        void destroy();

        ShaderStatus init(GLenum shader_type, const char* fp);
        

        ShaderStatus compile();

        GLuint getHandle();
        GLenum getShaderType();

        
};


