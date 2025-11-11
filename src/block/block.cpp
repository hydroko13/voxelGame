#include "block.h"

Block::Block() {
    
}

Block::Block(ImageAtlas &atlas, std::string topFace, std::string bottomFace, std::string northFace, std::string southFace, std::string westFace, std::string eastFace) {
    this->texCoordsTopFace = atlas.getTexCoords(topFace);
    this->texCoordsBottomFace = atlas.getTexCoords(bottomFace);
    this->texCoordsWestFace = atlas.getTexCoords(westFace);
    this->texCoordsEastFace = atlas.getTexCoords(eastFace);
    this->texCoordsSouthFace = atlas.getTexCoords(southFace);
    this->texCoordsNorthFace = atlas.getTexCoords(northFace);



}
