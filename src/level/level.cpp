#include "level.h"


Level::Level() {
   
}

void Level::generateChunks(int threadId) {


    int leftBound = -12;
    int rightBound = 12;
    int upBound = 12;
    int downBound = -12;
    int xstep = 1;
    int zstep = 1;


    if (threadId == 0) {
        leftBound = 0;
        rightBound = 12;
        upBound = 12;
        downBound = 0;
        zstep = 1;
        xstep = 1;
    }
    else if (threadId == 1) {
        leftBound = 0;
        rightBound = -12;
        upBound = 12;
        downBound = 0;
        zstep = 1;
        xstep = -1;
    }
    else if (threadId == 2) {
        leftBound = 0;
        rightBound = 12;
        upBound = -12;
        downBound = 0;
        zstep = -1;
        xstep = 1;
    }
    else if (threadId == 3) {
        leftBound = 0;
        rightBound = -12;
        upBound = -12;
        downBound = 0;
        zstep = -1;
        xstep = -1;
    }

   

    std::this_thread::sleep_for(std::chrono::milliseconds(10*threadId));
    
    std::cout << threadId << "\n";

    while (!stopGen.load()) {


        int ox = chunkGenOriginX.load();
        int oz = chunkGenOriginY.load();
        

        for (int x = ox + leftBound; x != ox + rightBound; x+=xstep) {
            for (int z = oz + downBound; z != oz + upBound; z+=zstep) {
                glm::ivec2 cPos(x, z);



                chunksMutex.lock();

                auto p = this->chunks.try_emplace(cPos, cPos);
                if (p.second) {

                    Chunk& chunk = p.first->second;



                    if (!chunk.generated) {
                        chunk.generate(worldGen);

                    }




                    chunksMutex.unlock();

                    chunkstoinitMutex.lock();

                    this->chunkstoinit.push(cPos);

                    chunkstoinitMutex.unlock();

                }
                else {
                    chunksMutex.unlock();
                }


                
                std::this_thread::sleep_for(std::chrono::milliseconds(35));

            }
        }


           
        

    
        

       
        



        

    }


   
}

void Level::startChunkGenerationThread() {
    
    

  


    for (int i = 0; i < 4; i++) {
        this->chunkGenThreads.push_back(std::thread(&Level::generateChunks, this, i));
    }
    


   
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
void Level::setBlockAt(glm::ivec3 pos, unsigned char blockByte, BlockRegistry& blockRegistry) {

    glm::ivec2 chunkPos(glm::floor((float)pos.x / 16), glm::floor((float)pos.z / 16));

    chunksMutex.lock();

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

    chunksMutex.unlock();


}

void Level::drawChunks(ShaderProgram& shaderProgram, BlockRegistry& blockRegistry) {


    //chunksMutex.lock();
    //for (auto& p : this->chunks) {
    //    float dist = glm::distance(glm::fvec2(p.second.chunkPos), glm::fvec2(this->chunkGenOriginX.load(), this->chunkGenOriginY.load()));
    //    if (dist > 5.0f) {
    //        p.second.destroy();

    //        this->chunks.erase(p.second.chunkPos);

    //    }
    //    
    //}
    //chunksMutex.unlock();



    
    
    //std::cout << "dx " << this->chunkGenOrigin.x << std::endl;

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
    for (int x =  this->chunkGenOriginX.load()-12; x < this->chunkGenOriginX.load() + 12; x++) {
        for (int z = -this->chunkGenOriginY.load()-12; z < this->chunkGenOriginY.load() + 12; z++) {
           
           
            
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