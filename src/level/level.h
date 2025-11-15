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
#include "../worldgen/worldgen.h"

class Level {
public:
	std::unordered_map<glm::ivec2, Chunk> chunks;
	std::shared_mutex chunksMutex;
	std::mutex chunkstoinitMutex;
	std::thread chunkGenThread1;
	std::thread chunkGenThread2;
	std::thread chunkGenThread3;
	std::thread chunkGenThread4;
	glm::ivec2 chunkGenOrigin;

	std::queue<glm::ivec2> chunkstoinit;

	WorldGen worldGen;

	bool doneGame = false;



	Level();

	void generateChunks(int quadrant);

	void startChunkGenerationThread();

	

	void drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry);



};