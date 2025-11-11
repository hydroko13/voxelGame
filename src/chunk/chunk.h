#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include "../image/image.h"
#include "../blockRegistry/blockRegistry.h"
#include "../block/block.h"
#include "../vertexBuffer/vertexBuffer.h"
#include "../elementBuffer/elementBuffer.h"
#include "../vertexArray/vertexArray.h"
#include "../chunkData/chunkData.h"



class Chunk {
public:

	glm::ivec2 chunkPos;
	ChunkData data;
	VertexBuffer vbo;
	ElementBuffer ebo;
	VertexArray vao;

	Chunk(glm::ivec2 chunkPos);
	~Chunk();

	void generate();

	void updateVBO(BlockRegistry& blockRegistry);

	void init();


};