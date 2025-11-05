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
        GLuint shader_gpu_handle;
        GLenum shader_type;
        bool initalized;
        bool compiled;
        std::string filename;

        std::string shader_source_code;
        

    public:
        Shader();
        ~Shader();

        ShaderStatus init(GLenum shader_type, const char* fp);


        ShaderStatus compile();

        
};


