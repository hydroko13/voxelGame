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
#include "../shaderProgram/shaderProgram.h"
#include "../worldgen/worldgen.h"
#include <tuple>	



class Chunk {
public:

	glm::ivec2 chunkPos;
	ChunkData data;
	VertexBuffer vbo;
	ElementBuffer ebo;
	VertexArray vao;
	glm::mat4 model;
	bool initialized = false;
	bool generated = false;

	std::vector<float> vertices;
	std::vector<unsigned int> indices;


	Chunk(glm::ivec2 pos);
	Chunk(const Chunk& chunk);

	void generate(WorldGen& worldgen);

	void updateVBO();

	void updateMesh(BlockRegistry& blockRegistry);

	void destroy();

	void draw(ShaderProgram& shaderProgram);

	void init();


};