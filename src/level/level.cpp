#include "level.h"


Level::Level() {
   
}

void Level::generateChunks(int threadId) {





    
    std::cout << threadId << "\n";

    while (!stopGen.load()) {


        int ox = chunkGenOriginX.load();
        int oz = chunkGenOriginY.load();

        std::map<float, glm::ivec2> chunksSorted;
        chunksMutex.lock();
        chunkstoinitMutex.lock();
        for (int x = ox - 10; x < ox + 10; x++) {
            for (int z = oz - 10; z < oz + 10; z++) {
                glm::ivec2 cPos(x, z);
                float dist = glm::distance(glm::fvec2(cPos), glm::fvec2(ox, oz));
                if (!chunks.contains(cPos)) {
                    chunksSorted.try_emplace(dist, x, z);
                }
                
            }
        }
        chunksMutex.unlock();
        chunkstoinitMutex.unlock();

        

        for (auto& p: chunksSorted) {
            chunksMutex.lock();
            
            auto p2 = this->chunks.try_emplace(p.second, p.second);
            

            Chunk &chunk = p2.first->second;

            if (!chunk.generated)
            {
                chunk.generate(worldGen);
            }
            chunksMutex.unlock();

            chunkstoinitMutex.lock();
            this->chunkstoinit.push(p.second);
            chunkstoinitMutex.unlock();
           
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }


}


   


void Level::startChunkGenerationThread() {
    
    

  


    for (int i = 0; i < 1; i++) {
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

    chunksMutex.lock();

    for (int i = 0; i < 2; i++) {
        if (!this->chunkstoinit.empty()) {

            glm::ivec2 chunkToInitPos = this->chunkstoinit.front();


           
            
            

           

                

            Chunk& chunk = this->chunks.at(chunkToInitPos);






            chunk.init();
            chunk.updateMesh(blockRegistry);
            chunk.updateVBO();

            



            

                
            
            this->chunkstoinit.pop();




        }
    }

    chunksMutex.unlock();

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