#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "../shader/shader.h"
#include <vector>
#include "../glerror/glerror.h"
#include <glm/gtc/type_ptr.hpp>


enum class ShaderProgramStatus {
	LinkedSuccessfully,
	LinkFailed,
};

class ShaderProgram {
private:
	GLuint program_gpu_handle = NULL;
	
	


public:

	ShaderProgram();
	void destroy();

	void init();

	void attachShader(Shader& shader);

	void use();

	void setInt(const char* name, int v);

	void setFloat(const char* name, float v);

	void setMat4f(const char* name, glm::mat4& v);

	ShaderProgramStatus link();

	



};