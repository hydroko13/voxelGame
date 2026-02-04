#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include "../image/image.h"
#include "../vertexBuffer/vertexBuffer.h"
#include "../elementBuffer/elementBuffer.h"
#include "../vertexArray/vertexArray.h"
#include "../imageAtlas/imageAtlas.h"
#include "../shaderProgram/shaderProgram.h"
#include <tuple>	

class BlockSelectorBox {
public:
	VertexBuffer vbo;
	ElementBuffer ebo;
	VertexArray vao;
	glm::mat4 model;
	int destroy_progress = 0;


	float vertices[120] = {
		
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 0.0f,


		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 0.0f,


		0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	};

	unsigned int indices[36] = {
		2, 1, 0,
		0, 3, 2,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		14, 13, 12,
		12, 15, 14,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,

	};

	BlockSelectorBox();

	void destroy();

	void draw(ShaderProgram& shaderProgram);

	void goTo(glm::ivec3 blockPos);

	void updateFrame(ImageAtlas& blockAtlas);


	void init(ImageAtlas& blockAtlas);
};

