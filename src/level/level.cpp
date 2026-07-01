#include "level.h"


Level::Level() {
   
}

void Level::generateChunks(int threadId) {


    


}

void Level::genChunks(BlockRegistry &blockRegistry)
{

    std::cout << "dad" << std::endl;
    for (int x = (this->chunkGenOrigin.x - 3); x < (this->chunkGenOrigin.x + 3); x++)
    {
        for (int z = (this->chunkGenOrigin.y - 3); z < (this->chunkGenOrigin.y + 3); z++)
        {
            glm::ivec2 pos(x, z);
            if (!this->chunks.contains(pos))
            {
                Chunk chunk(pos);

                chunk.generate(worldGen);
                chunk.updateMesh(blockRegistry);

                
                chunks.emplace(pos, std::move(chunk));


            }
        }
    }
}

unsigned char Level::getBlockAt(glm::ivec3 blockPos) {

    glm::ivec2 chunkPos(glm::floor((float)blockPos.x / 16), glm::floor((float)blockPos.z / 16));

    

    bool exists = this->chunks.contains(chunkPos);

    

    if (exists) {


        Chunk& chunk = this->chunks.at(chunkPos);

        

        int x = 0;
        int z = 0;

       

        
        x = ((blockPos.x % 16) + 16) % 16;
        z = ((blockPos.z % 16) + 16) % 16;
        



        
        
       

        return chunk.data.getBlock(glm::ivec3(x, blockPos.y, z));

        

    }


    return 0;

    
}
void Level::setBlockAt(glm::ivec3 pos, unsigned char blockByte, BlockRegistry& blockRegistry) {

    glm::ivec2 chunkPos(glm::floor((float)pos.x / 16), glm::floor((float)pos.z / 16));


    bool exists = this->chunks.contains(chunkPos);



    if (exists) {


        Chunk& chunk = this->chunks.at(chunkPos);



        int x = 0;
        int z = 0;




        x = ((pos.x % 16) + 16) % 16;
        z = ((pos.z % 16) + 16) % 16;






        

        chunk.data.setBlock(glm::ivec3(x, pos.y, z), blockByte);
        chunk.updateMesh(blockRegistry);
        chunk.updateVBO();



    }
}

void Level::drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry) {

    for (int x = (this->chunkGenOrigin.x - 4); x < (this->chunkGenOrigin.x + 4); x++)
    {
        for (int z = (this->chunkGenOrigin.y - 4); z < (this->chunkGenOrigin.y + 4); z++)
        {

            if (this->chunks.contains(glm::ivec2(x, z)))
            {

                Chunk &chunk = this->chunks.at(glm::ivec2(x, z));

                if (!chunk.initialized) {
                    chunk.init();
                    chunk.updateVBO();
                    std::cout << "hello" << std::endl;

                }
            }
        }
    }

    std::vector<Chunk *> chunksToDraw;
    for (int x = (this->chunkGenOrigin.x - 12); x < (this->chunkGenOrigin.x + 12); x++)
    {
        for (int z = (this->chunkGenOrigin.y - 12); z < (this->chunkGenOrigin.y + 12); z++)
        {

            if (this->chunks.contains(glm::ivec2(x, z)))
            {

                Chunk &chunk = this->chunks.at(glm::ivec2(x, z));

                if (chunk.initialized)
                {
                    chunksToDraw.push_back(&chunk);
                }
            }
        }
    }

    for (Chunk *c : chunksToDraw)
    {
        c->draw(shaderProgram);
        // std::cout << "Helloworld\n";
    }
}