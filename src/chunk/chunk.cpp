#include "chunk.h"

Chunk::Chunk(glm::ivec2 pos) {
    model = glm::mat4(1.0f);
    this->chunkPos = pos;

}

Chunk::Chunk(const Chunk &chunk) {
    
    this->chunkPos = chunk.chunkPos;
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::fvec3(16.0f * chunkPos.x, 0.0f, 16.0f * chunkPos.y));
    

}

void Chunk::init() {

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::fvec3(16.0f * chunkPos.x, 0.0f, 16.0f * chunkPos.y));

    

    this->vao.init();

    this->vao.bind();

    

    this->vbo.init(GL_STATIC_DRAW);
    this->ebo.init(GL_STATIC_DRAW);

    this->vbo.bind();

    this->ebo.bind();

    this->vbo.setData((void*)this->vertices.data(), sizeof(float) * this->vertices.size());

    this->ebo.setData((void*)this->indices.data(), sizeof(unsigned int) * this->indices.size());

    this->vao.beginAttribs();


    

    this->vao.attrib(GL_FLOAT, 3, sizeof(float) * 3);
    this->vao.attrib(GL_FLOAT, 2, sizeof(float) * 2);

    this->vao.doneAttribs();

    this->vao.unbind();

    initialized = true;
    

   
    
}

void Chunk::updateMesh(BlockRegistry& blockRegistry) {
    this->vertices.clear();
    this->indices.clear();



    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {

                unsigned char blockByte = this->data.getBlock(glm::ivec3(x, y, z));

                unsigned char blockByteSouth = this->data.getBlock(glm::ivec3(x, y, z-1));
                unsigned char blockByteNorth = this->data.getBlock(glm::ivec3(x, y, z+1));
                unsigned char blockByteEast = this->data.getBlock(glm::ivec3(x+1, y, z));
                unsigned char blockByteWest = this->data.getBlock(glm::ivec3(x-1, y, z));
                unsigned char blockByteUp = this->data.getBlock(glm::ivec3(x, y+1, z));
                unsigned char blockByteDown = this->data.getBlock(glm::ivec3(x, y-1, z));

                unsigned int blockId = static_cast<unsigned int>(blockByte);
                

                if (blockId != 0) {
                    Block block = blockRegistry.getBlock(blockId);

                    std::tuple<float, float, float, float> texcoords1 = block.texCoordsNorthFace;
                    std::tuple<float, float, float, float> texcoords2 = block.texCoordsSouthFace;
                    std::tuple<float, float, float, float> texcoords3 = block.texCoordsEastFace;
                    std::tuple<float, float, float, float> texcoords4 = block.texCoordsWestFace;
                    std::tuple<float, float, float, float> texcoords5 = block.texCoordsBottomFace;
                    std::tuple<float, float, float, float> texcoords6 = block.texCoordsTopFace;

                    //this->vertices[3] = std::get<0>(coords);
                    //this->vertices[4] = std::get<1>(coords);

                    //this->vertices[8] = std::get<0>(coords);
                    //this->vertices[9] = std::get<3>(coords);
                    //this->vertices[13] = std::get<2>(coords);
                    //this->vertices[14] = std::get<3>(coords);

                    //this->vertices[18] = std::get<2>(coords);
                    //this->vertices[19] = std::get<1>(coords);

                    bool include_south_face = blockByteSouth == 0;
                    bool include_north_face = blockByteNorth == 0;
                    bool include_east_face = blockByteEast == 0;
                    bool include_west_face = blockByteWest == 0;
                    bool include_top_face = blockByteUp == 0;
                    bool include_bottom_face = blockByteDown == 0;

                    

                    if (include_south_face) {
                        float verts[20] = {
                           0.0f + (float)x, 0.0f + (float)y, 0.0f + (float)z,    std::get<2>(texcoords2), std::get<1>(texcoords2),
                           0.0f + (float)x, 1.0f + (float)y, 0.0f + (float)z,     std::get<2>(texcoords2), std::get<3>(texcoords2),
                           1.0f + (float)x, 1.0f + (float)y, 0.0f + (float)z,      std::get<0>(texcoords2), std::get<3>(texcoords2),
                           1.0f + (float)x, 0.0f + (float)y, 0.0f + (float)z,     std::get<0>(texcoords2), std::get<1>(texcoords2)

                        };

                        int vertex_vector_size = this->vertices.size() / 5;

                        unsigned int idxs[6] = {
                            vertex_vector_size + 2, vertex_vector_size + 1, vertex_vector_size + 0,
                            vertex_vector_size + 0, vertex_vector_size + 3, vertex_vector_size + 2
                        };

                        for (int i = 0; i < 20; i++) {
                            this->vertices.push_back(verts[i]);
                        }

                        for (int i = 0; i < 6; i++) {
                            this->indices.push_back(idxs[i]);
                        }
                    }

                    if (include_north_face) {
                        float verts[20] = {
                           0.0f + (float)x, 0.0f + (float)y, 1.0f + (float)z,    std::get<0>(texcoords1), std::get<1>(texcoords1),
                           0.0f + (float)x, 1.0f + (float)y, 1.0f + (float)z,     std::get<0>(texcoords1), std::get<3>(texcoords1),
                           1.0f + (float)x, 1.0f + (float)y, 1.0f + (float)z,      std::get<2>(texcoords1), std::get<3>(texcoords1),
                           1.0f + (float)x, 0.0f + (float)y, 1.0f + (float)z,     std::get<2>(texcoords1), std::get<1>(texcoords1)

                        };

                        int vertex_vector_size = this->vertices.size() / 5;

                        unsigned int idxs[6] = {
                            vertex_vector_size + 0, vertex_vector_size + 1, vertex_vector_size + 2,
                            vertex_vector_size + 2, vertex_vector_size + 3, vertex_vector_size + 0
                        };

                        for (int i = 0; i < 20; i++) {
                            this->vertices.push_back(verts[i]);
                        }

                        for (int i = 0; i < 6; i++) {
                            this->indices.push_back(idxs[i]);
                        }
                    }

                    if (include_east_face) {
                        float verts[20] = {
                           1.0f + (float)x, 0.0f + (float)y, 0.0f + (float)z,    std::get<2>(texcoords3), std::get<1>(texcoords3),
                           1.0f + (float)x, 0.0f + (float)y, 1.0f + (float)z,     std::get<0>(texcoords3), std::get<1>(texcoords3),
                           1.0f + (float)x, 1.0f + (float)y, 1.0f + (float)z,      std::get<0>(texcoords3), std::get<3>(texcoords3),
                           1.0f + (float)x, 1.0f + (float)y, 0.0f + (float)z,     std::get<2>(texcoords3), std::get<3>(texcoords3)

                        };

                        int vertex_vector_size = this->vertices.size() / 5;

                        unsigned int idxs[6] = {
                            vertex_vector_size + 0, vertex_vector_size + 1, vertex_vector_size + 2,
                            vertex_vector_size + 2, vertex_vector_size + 3, vertex_vector_size + 0
                        };

                        for (int i = 0; i < 20; i++) {
                            this->vertices.push_back(verts[i]);
                        }

                        for (int i = 0; i < 6; i++) {
                            this->indices.push_back(idxs[i]);
                        }
                    }

                    if (include_west_face) {
                        float verts[20] = {
                           0.0f + (float)x, 0.0f + (float)y, 0.0f + (float)z,    std::get<0>(texcoords4), std::get<1>(texcoords4),
                           0.0f + (float)x, 0.0f + (float)y, 1.0f + (float)z,     std::get<2>(texcoords4), std::get<1>(texcoords4),
                           0.0f + (float)x, 1.0f + (float)y, 1.0f + (float)z,      std::get<2>(texcoords4), std::get<3>(texcoords4),
                           0.0f + (float)x, 1.0f + (float)y, 0.0f + (float)z,     std::get<0>(texcoords4), std::get<3>(texcoords4),

                        };

                        int vertex_vector_size = this->vertices.size() / 5;

                        unsigned int idxs[6] = {
                            vertex_vector_size + 2, vertex_vector_size + 1, vertex_vector_size + 0,
                            vertex_vector_size + 0, vertex_vector_size + 3, vertex_vector_size + 2
                        };

                        for (int i = 0; i < 20; i++) {
                            this->vertices.push_back(verts[i]);
                        }

                        for (int i = 0; i < 6; i++) {
                            this->indices.push_back(idxs[i]);
                        }
                    }

                    if (include_bottom_face) {
                        float verts[20] = {
                           0.0f + (float)x, 0.0f + (float)y, 1.0f + (float)z,    std::get<2>(texcoords5), std::get<1>(texcoords5),
                           0.0f + (float)x, 0.0f + (float)y, 0.0f + (float)z,     std::get<2>(texcoords5), std::get<3>(texcoords5),
                           1.0f + (float)x, 0.0f + (float)y, 0.0f + (float)z,      std::get<0>(texcoords5), std::get<3>(texcoords5),
                           1.0f + (float)x, 0.0f + (float)y, 1.0f + (float)z,     std::get<0>(texcoords5), std::get<1>(texcoords5)

                        };

                        int vertex_vector_size = this->vertices.size() / 5;

                        unsigned int idxs[6] = {
                            vertex_vector_size + 2, vertex_vector_size + 1, vertex_vector_size + 0,
                            vertex_vector_size + 0, vertex_vector_size + 3, vertex_vector_size + 2
                        };

                        for (int i = 0; i < 20; i++) {
                            this->vertices.push_back(verts[i]);
                        }

                        for (int i = 0; i < 6; i++) {
                            this->indices.push_back(idxs[i]);
                        }
                    }

                    if (include_top_face) {
                        float verts[20] = {
                           0.0f + (float)x, 1.0f + (float)y, 1.0f + (float)z,    std::get<0>(texcoords6), std::get<1>(texcoords6),
                           0.0f + (float)x, 1.0f + (float)y, 0.0f + (float)z,     std::get<0>(texcoords6), std::get<3>(texcoords6),
                           1.0f + (float)x, 1.0f + (float)y, 0.0f + (float)z,      std::get<2>(texcoords6), std::get<3>(texcoords6),
                           1.0f + (float)x, 1.0f + (float)y, 1.0f + (float)z,     std::get<2>(texcoords6), std::get<1>(texcoords6)

                        };

                        int vertex_vector_size = this->vertices.size() / 5;

                        unsigned int idxs[6] = {
                            vertex_vector_size + 0, vertex_vector_size + 1, vertex_vector_size + 2,
                            vertex_vector_size + 2, vertex_vector_size + 3, vertex_vector_size + 0
                        };

                        for (int i = 0; i < 20; i++) {
                            this->vertices.push_back(verts[i]);
                        }

                        for (int i = 0; i < 6; i++) {
                            this->indices.push_back(idxs[i]);
                        }
                    }


                    


                }

                

            }
        }
    }
}

void Chunk::updateVBO() {
    this->vbo.bind();

    this->ebo.bind();

    this->vbo.setData((void*)this->vertices.data(), sizeof(float) * this->vertices.size());

    this->ebo.setData((void*)this->indices.data(), sizeof(unsigned int) * this->indices.size());
}

void Chunk::draw(ShaderProgram& shaderProgram) {

    shaderProgram.setMat4f("model", this->model);
    this->vao.bind();
    glCheckErrorBefore("glDrawElements");
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glCheckErrorAfter("glDrawElements");


}

void Chunk::destroy() {
    this->vbo.destroy();
    this->vao.destroy();
    this->ebo.destroy();
}

void Chunk::generate(WorldGen& worldgen) {

    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {

                glm::ivec3 blockPos = glm::ivec3(x + chunkPos.x * 16, y, z + chunkPos.y * 16);
                
                
                int h = worldgen.blockHeightAt(glm::ivec2(blockPos.x, blockPos.z));
                if (y == h) {
                    this->data.setBlock(glm::ivec3(x, y, z), 2);
                }

                else if (y < h && y > h - 5) {
                    this->data.setBlock(glm::ivec3(x, y, z), 3);
                }

                else if (y < h && y <= h - 5) {
                    this->data.setBlock(glm::ivec3(x, y, z), 4);
                }


                
                
            }
        }
    }
    generated = true;
}

