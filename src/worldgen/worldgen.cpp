#include "worldgen.h"

WorldGen::WorldGen() {
	this->noise1.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);

}

int WorldGen::blockHeightAt(glm::ivec2 pos) {

	float x = (((float)pos.x * 1.5f));
	float y = (((float)pos.y * 1.5f));



	float v = this->noise1.GetNoise(x, y) * 5.0f;

	return floor(v) + 64;


}




