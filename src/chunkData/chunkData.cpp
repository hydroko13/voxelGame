#include "./chunkData.h"


ChunkData::ChunkData() {
    this->data = (unsigned char*) malloc(16 * 16 * 256 * 1);

    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                this->setBlock(glm::ivec3(x, y, z), 0);
            }
        }
    }
}

ChunkData::~ChunkData() {
    free(this->data);
}

void ChunkData::setBlock(glm::ivec3 blockPos, unsigned int blockID) {

    unsigned char blockByte = static_cast<unsigned char>(blockID);
    


    this->data[(blockPos.y * (16 * 16)) + (blockPos.x * 16) + blockPos.z] = blockByte;
}