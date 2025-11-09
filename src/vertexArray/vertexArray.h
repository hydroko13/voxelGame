#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../glerror/glerror.h"
#include <string>
#include <fstream>
#include <filesystem>
#include "../shader/shader.h"
#include <vector>
#include <type_traits>
#include "../vertexAttribute/vertexAttribute.h"

class VertexArray {

	private:
		GLuint vao_gpu_handle = NULL;
		std::vector<VertexAttribute> attrs;

		




	public:

		



		VertexArray();

		void destroy();


		void init();

		void beginAttribs();

		void attrib(GLenum type, int count, int size);

		void doneAttribs();

		void bind();

		void unbind();
		

};





