#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include <unordered_map>
#include "../image/image.h"
#include "../block/block.h"

class BlockRegistry {
private:
	std::unordered_map<unsigned int, Block> blocks;

public:
	BlockRegistry();

	Block& getBlock(unsigned int id);
	void registerBlock(unsigned int id, Block block);
};