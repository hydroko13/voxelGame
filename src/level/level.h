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
#include "../worldgen/worldgen.h"


class Level {
public:
	std::unordered_map<glm::ivec2, Chunk> chunks;
	std::shared_mutex chunksMutex;
	std::mutex chunkstoinitMutex;
	std::vector<std::thread> chunkGenThreads;

	std::atomic<int> chunkGenOriginX{ 0 };
	std::atomic<int> chunkGenOriginY{ 0 };


	glm::ivec2 lastSpiralStartPos;

	std::queue<glm::ivec2> chunkstoinit;

	WorldGen worldGen;

	glm::ivec2 chunkgencurrentorg;

	std::atomic<bool> stopGen{ false };





	Level();

	void generateChunks(int threadId);



	void startChunkGenerationThread();

	void resetChunkSpiral();
	

	void drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry);



};