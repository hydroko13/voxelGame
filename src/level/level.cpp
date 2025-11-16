#include "level.h"


Level::Level() {
   
}

void Level::generateChunks(int threadId) {



    
    int x = chunkGenOriginX.load();
    int z = chunkGenOriginY.load();
    int spiralStage = 0;
    int spiralOriginZ = 0;
    int spiralOriginX = 0;
    int spiralLoop = 1;
    int spiralOrgX = x;
    int spiralOrgZ = z;


    for (int i = 0; i < threadId; i++) {
        if (spiralStage == 0) {
            x -= 1;
            spiralOriginZ = z;
            spiralStage = 1;
        }

        else if (spiralStage == 1) {
            z += 1;
            if (abs(z - spiralOriginZ) >= spiralLoop) {
                spiralStage = 2;
                spiralOriginX = x;
            }

        }
        else if (spiralStage == 2) {
            x += 1;
            if (abs(x - spiralOriginX) >= spiralLoop + 1) {
                spiralStage = 3;
                spiralOriginZ = z;
            }

        }
        else if (spiralStage == 3) {
            z -= 1;
            if (abs(z - spiralOriginZ) >= spiralLoop + 1) {
                spiralStage = 4;
                spiralOriginX = x;
            }

        }

        else if (spiralStage == 4) {
            x -= 1;
            if (abs(x - spiralOriginX) >= spiralLoop + 2) {
                spiralStage = 1;
                spiralOriginZ = z;
                spiralLoop += 2;

            }

        }
    }
  

    while (!stopGen.load()) {

        

        while (true) {
            bool generatedOneChunk = false;

            glm::ivec2 cPos(x, z);



            chunksMutex.lock();

            auto p = this->chunks.try_emplace(cPos, cPos);
            if (p.second) {
                chunksMutex.unlock();
                Chunk& chunk = p.first->second;



                if (!chunk.generated) {
                    generatedOneChunk = true;
                    chunk.generate(worldGen);

                }






                chunkstoinitMutex.lock();

                this->chunkstoinit.push(cPos);

                chunkstoinitMutex.unlock();

            }
            else {
                chunksMutex.unlock();
            }

            for (int i = 0; i < 8; i++) {
                if (spiralStage == 0) {
                    x -= 1;
                    spiralOriginZ = z;
                    spiralStage = 1;
                }

                else if (spiralStage == 1) {
                    z += 1;
                    if (abs(z - spiralOriginZ) >= spiralLoop) {
                        spiralStage = 2;
                        spiralOriginX = x;
                    }

                }
                else if (spiralStage == 2) {
                    x += 1;
                    if (abs(x - spiralOriginX) >= spiralLoop + 1) {
                        spiralStage = 3;
                        spiralOriginZ = z;
                    }

                }
                else if (spiralStage == 3) {
                    z -= 1;
                    if (abs(z - spiralOriginZ) >= spiralLoop + 1) {
                        spiralStage = 4;
                        spiralOriginX = x;
                    }

                }

                else if (spiralStage == 4) {
                    x -= 1;
                    if (abs(x - spiralOriginX) >= spiralLoop + 2) {
                        spiralStage = 1;
                        spiralOriginZ = z;
                        spiralLoop += 2;

                    }

                }
            }

            if (generatedOneChunk) {
                break;
            }

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    }


   
}

void Level::startChunkGenerationThread() {
    
    

    lastSpiralStartPos = glm::ivec2(chunkGenOriginX.load(), chunkGenOriginY.load());


    for (int i = 0; i < 8; i++) {
        this->chunkGenThreads.push_back(std::thread(&Level::generateChunks, this, i));
    }
    


   
}
void Level::resetChunkSpiral() {



    stopGen.store(true);

    for (std::thread& t : chunkGenThreads) {
        
        t.join();
        

    }


    


    this->chunkGenThreads.clear();

    stopGen.store(false);


    this->startChunkGenerationThread();
    
}


unsigned char Level::getBlockAt(glm::ivec3 blockPos) {

    glm::ivec2 chunkPos(glm::floor((float)blockPos.x / 16), glm::floor((float)blockPos.z / 16));

    chunksMutex.lock();

    bool exists = this->chunks.contains(chunkPos);

    

    if (exists) {


        Chunk& chunk = this->chunks.at(chunkPos);

        

        int x = 0;
        int z = 0;

       

        
        x = ((blockPos.x % 16) + 16) % 16;
        z = ((blockPos.z % 16) + 16) % 16;
        



        
        
        chunksMutex.unlock();

        return chunk.data.getBlock(glm::ivec3(x, blockPos.y, z));

        

    }

    chunksMutex.unlock();

    return 0;

    
}

void Level::drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry) {


    
    
    //std::cout << "dx " << this->chunkGenOrigin.x << std::endl;

    glm::fvec2 currentChunkPos = glm::ivec2(chunkGenOriginX.load(), chunkGenOriginY.load());

    if (glm::distance(currentChunkPos, glm::fvec2(lastSpiralStartPos)) > 4.0f) {
        this->resetChunkSpiral();
    }
     
    chunkstoinitMutex.lock();


    for (int i = 0; i < 2; i++) {
        if (!this->chunkstoinit.empty()) {

            glm::ivec2 chunkToInitPos = this->chunkstoinit.front();

            chunksMutex.lock_shared();

            bool exists = this->chunks.contains(chunkToInitPos);

            chunksMutex.unlock_shared();

            if (exists) {

                chunksMutex.lock();

                Chunk& chunk = this->chunks.at(chunkToInitPos);

                




                chunk.init();
                chunk.updateMesh(blockRegistry);
                chunk.updateVBO();

                chunksMutex.unlock();



            }

            this->chunkstoinit.pop();




        }
    }

    chunkstoinitMutex.unlock();
    

    std::vector<Chunk*> chunksToDraw;
    chunksMutex.lock();
    for (int x = -15+this->chunkGenOriginX.load(); x < 15 + this->chunkGenOriginX.load(); x++) {
        for (int z = -15 + this->chunkGenOriginY.load(); z < 15 + this->chunkGenOriginY.load(); z++) {
           
            if (this->chunks.contains(glm::ivec2(x, z))) {
                
                Chunk& chunk = this->chunks.at(glm::ivec2(x, z));

                if (chunk.initialized) {
                    chunksToDraw.push_back(&chunk);
                   
                }

                
            }

            
           

        }
    }
    chunksMutex.unlock();

    for (Chunk* c : chunksToDraw) {
        c->draw(shaderProgram);
    }
    

   
}