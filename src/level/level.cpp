#include "level.h"

Level::Level() {
    
}

void Level::generateChunks(int quadrant) {

    std::this_thread::sleep_for(std::chrono::milliseconds(quadrant*25));


    while (!this->doneGame) {

        int x1 = 0;
        int x2 = 0;
        int z1 = 0;
        int z2 = 0;
        int xstep = 0;
        int zstep = 0;

        if (quadrant == 1) {
            x1 = chunkGenOrigin.x + 0;
            x2 = chunkGenOrigin.x + 6;
            z1 = chunkGenOrigin.y + 0;
            z2 = chunkGenOrigin.y + 6;
            xstep = 1;
            zstep = 1;
        }
        if (quadrant == 2) {
            x1 = chunkGenOrigin.x + 0;
            x2 = chunkGenOrigin.x + -6;
            z1 = chunkGenOrigin.y + 0;
            z2 = chunkGenOrigin.y + 6;
            xstep = -1;
            zstep = 1;
        }
        if (quadrant == 3) {
            x1 = chunkGenOrigin.x + 0;
            x2 = chunkGenOrigin.x + -6;
            z1 = chunkGenOrigin.y + 0;
            z2 = chunkGenOrigin.y + -6;
            xstep = -1;
            zstep = -1;
        }
        if (quadrant == 4) {
            x1 = chunkGenOrigin.x + 0;
            x2 = chunkGenOrigin.x + 6;
            z1 = chunkGenOrigin.y + 0;
            z2 = chunkGenOrigin.y + -6;
            xstep = 1;
            zstep = -1;
        }
        

        for (int x = x1; x != x2; x+=xstep) {
            for (int z = z1; z != z2; z+=zstep) {

                glm::ivec2 cPos(x, z);



                chunksMutex.lock_shared();
                
                auto p = this->chunks.try_emplace(cPos, cPos);
                if (p.second) {
                    chunksMutex.unlock_shared();
                    Chunk& chunk = p.first->second;

                    

                    if (!chunk.generated) {
                        chunk.generate(worldGen);
                    }






                    chunkstoinitMutex.lock();

                    this->chunkstoinit.push(cPos);

                    chunkstoinitMutex.unlock();

                }
                else {
                    chunksMutex.unlock_shared();
                }
                
                   
                
                

          

                
                
            }
            
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Level::startChunkGenerationThread() {
    this->chunkGenOrigin = glm::ivec2(0, 0);
    chunkGenThread1 = std::thread(&Level::generateChunks, this, 1);
    chunkGenThread2 = std::thread(&Level::generateChunks, this, 2);
    chunkGenThread3 = std::thread(&Level::generateChunks, this, 3);
    chunkGenThread4 = std::thread(&Level::generateChunks, this, 4);

   
}

void Level::drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry) {


    
    //std::cout << "dx " << this->chunkGenOrigin.x << std::endl;

    chunkstoinitMutex.lock();


    if (!this->chunkstoinit.empty()) {

        glm::ivec2 chunkToInitPos = this->chunkstoinit.front();

        chunksMutex.lock_shared();

        bool exists = this->chunks.contains(chunkToInitPos);

        chunksMutex.unlock_shared();

        if (exists) {

            chunksMutex.lock_shared();

            Chunk& chunk = this->chunks.at(chunkToInitPos);

            chunksMutex.unlock_shared();

            chunk.init();
            chunk.updateMesh(blockRegistry);
            chunk.updateVBO();

           

        }

        this->chunkstoinit.pop();

       

        
    }

    chunkstoinitMutex.unlock();
    

    for (int x = -10+this->chunkGenOrigin.x; x < 10 + this->chunkGenOrigin.x; x++) {
        for (int z = -10 + this->chunkGenOrigin.y; z < 10 + this->chunkGenOrigin.y; z++) {
            chunksMutex.lock_shared();
            if (this->chunks.contains(glm::ivec2(x, z))) {
                
                Chunk& chunk = this->chunks.at(glm::ivec2(x, z));

                /*chunk.generate();

                chunk.init(glm::ivec2(0, 0));



                chunk.updateMesh(blockRegistry);
                chunk.updateVBO();*/
                if (chunk.initialized) {
                    chunk.draw(shaderProgram);
                }

                
            }

            chunksMutex.unlock_shared();
           

        }
    }
    

   
}