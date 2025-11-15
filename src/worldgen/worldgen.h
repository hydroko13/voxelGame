#pragma once

#include <FastNoiseLite.h>
#include <random>
#include <iostream>
#include  <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class WorldGen {
public:
	FastNoiseLite noise1;

	int seed = 151;

	WorldGen();

	int blockHeightAt(glm::ivec2 pos);


};

