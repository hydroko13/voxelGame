#include "chunk.h"

Chunk::Chunk(glm::ivec2 pos) {
    this->chunkPos = pos;
}

void Chunk::init() {
    
    this->vao.init();

    this->vao.bind();

    

    this->vbo.init(GL_STATIC_DRAW);
    this->ebo.init(GL_STATIC_DRAW);

    this->vao.beginAttribs();

    

    this->vao.attrib(GL_FLOAT, 3, sizeof(float) * 3);
    this->vao.attrib(GL_FLOAT, 2, sizeof(float) * 2);

    this->vao.doneAttribs();

    this->vao.unbind();

    
}

void Chunk::updateVBO(BlockRegistry& blockRegistry) {
    
}

Chunk::~Chunk() {
    this->vbo.destroy();
    this->vao.destroy();
    this->ebo.destroy();
}