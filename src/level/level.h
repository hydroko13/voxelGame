#pragma once

#include <glad/glad.h>
#include  <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "../glerror/glerror.h"
#include <iostream>
#include <unordered_map>
#include "../chunk/chunk.h"
#include "../chunkData/chunkData.h"
#include "../shaderProgram/shaderProgram.h"
#include <cmath>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"
#include "../blockRegistry/blockRegistry.h"
#include <vector>
#include <thread>
#include <utility>
#include <shared_mutex>
#include <mutex>
#include <queue>
#include <random>
#include <atomic>
#include <map>
#include "../worldgen/worldgen.h"
#include <random>


class Level {
public:
	std::unordered_map<glm::ivec2, Chunk> chunks;
	std::mutex chunksToInitMutex;
	std::mutex chunksToGenMutex;
	std::vector<std::thread> chunkGenThreads;

	glm::ivec2 chunkGenOrigin{ 0, 0 };

	std::queue<Chunk> chunksToInit;
	std::queue<glm::ivec2> chunksToGen;

	WorldGen worldGen;

	glm::ivec2 chunkgencurrentorg;

	bool stopGen = false;





	Level();

	void generateChunks(int threadId);

	void setBlockAt(glm::ivec3 pos, unsigned char blockByte, BlockRegistry& blockRegistry);

	unsigned char getBlockAt(glm::ivec3 blockPos);


	void startChunkGenerationThread();	

	void drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry);



};