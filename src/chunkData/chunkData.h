#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include "../image/image.h"

class ChunkData {

private:
		unsigned char* data = new unsigned char[16 * 16 * 256 * 1];

public:

	ChunkData();

	~ChunkData();

	void setBlock(glm::ivec3 blockPos, unsigned int blockID);




};