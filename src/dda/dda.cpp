#include "dda.h"

DDA::DDA(glm::fvec3 pos, glm::fvec3 dir) {
	voxelX = floor(pos.x);
	voxelY = floor(pos.y);
	voxelZ = floor(pos.z);

	this->startPos = pos;
	this->directionVectorNormalized = dir;

	stepX = (this->directionVectorNormalized.x > 0) ? 1 : -1;
	stepY = (this->directionVectorNormalized.y > 0) ? 1 : -1;
	stepZ = (this->directionVectorNormalized.z > 0) ? 1 : -1;


}

void DDA::takeStep() {

}

// FINISH DDA