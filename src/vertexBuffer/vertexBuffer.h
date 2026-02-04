#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../glerror/glerror.h"


class VertexBuffer {

private:
	GLuint vbo_gpu_handle = NULL;
	GLenum usage;
	

public:


	VertexBuffer();

	void destroy();




	void init(GLenum usage);

	void setData(void* data, int size);

	void bind();

};


