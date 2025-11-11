#include "./blockRegistry.h"

BlockRegistry::BlockRegistry()
{
}

Block& BlockRegistry::getBlock(unsigned int id) {
    return this->blocks[id];
}

void BlockRegistry::registerBlock(unsigned int id, Block block) {
    std::pair<unsigned int, Block> p(id, block);
    this->blocks.insert(p);
}